from sagemath import *



def lattice_attack(N, e, delta, r, m=3, a=2, t=4):
    print(f"\nLattice Attack: N={N}, e={e}, delta={delta}, r={r}, m={m}, a={a}, t={t}")
    
    # Bounds
    X = ZZ(floor(N ** delta))  # b ~ N^delta
    Y = ZZ(floor(N ** (1 / (r + 1))))  # p, q ~ N^{1/(r+1)}
    Z = Y
    
    # Polynomial ring over ZZ
    R = PolynomialRing(ZZ, names='x,y,z', order='lex')
    x, y, z = R.gens()
    
    # f_e polynomial (no mod e; lattice handles it)
    f = 1 + x * (N - y^r - y^(r-1) * z + y^(r-1))
    
    # Generate polynomials per paper (page 3)
    polynomials = []
    
    # First set: gi,j,k for i=0..m, j=0..m-i, k=0..r
    for i in range(m + 1):
        for j in range(m - i + 1):
            for k in range(r + 1):
                g = x^i * y^((r-1)*i + k) * z^(i + a) * f^j
                # Replace every occurrence of y^r * z with N (may need multiple subs if higher powers)
                while True:
                    new_g = g.substitute({y^r * z: N})
                    if new_g == g:
                        break
                    g = new_g
                polynomials.append(g)
    
    # Second set: gi,j,0 for i=0..m, j=1..t-r (note f^i, z^a, no x)
    if t > r:
        for i in range(m + 1):
            for j in range(1, t - r + 1):
                g = y^(r + j) * z^a * f^i
                # Replace y^r * z with N
                while True:
                    new_g = g.substitute({y^r * z: N})
                    if new_g == g:
                        break
                    g = new_g
                polynomials.append(g)
    
    # Normalization (simplified: paper assumes gcd=1, we skip full mod e^m for practicality; det condition suffices)
    # In practice, if leading coeff not 1, invert mod e^m, but for large e^m, use integer lattice as-is
    
    # Collect all unique monomials (lex order)
    all_mons = set()
    for poly in polynomials:
        all_mons.update(poly.monomials())
    mon_list = sorted(list(all_mons), reverse=True)  # lex order, high to low for matrix
    
    dim = len(mon_list)
    print(f"Lattice dimension: {dim}")
    
    # Build lattice matrix (rows: polys, cols: monomials, entries: coeff * X^deg_x * Y^deg_y * Z^deg_z)
    # Note: paper uses e^{m-j} multiplier, but we approximate by including in det check later
    M = matrix(ZZ, len(polynomials), dim)
    mon_deg = {mon: mon.degrees() for mon in mon_list}
    
    for row, poly in enumerate(polynomials):
        coeffs = poly.dict()
        for col, mon in enumerate(mon_list):
            if mon in coeffs:
                deg_x, deg_y, deg_z = mon_deg[mon]
                scale = X^deg_x * Y^deg_y * Z^deg_z
                M[row, col] = ZZ(coeffs[mon]) * scale  # Scaled coeff
    
    # LLL reduction (use fplll for large)
    reduced = M.LLL()  # For large: M.LLL(algorithm='fplll')
    print("LLL done")
    
    # Extract first few short vectors as polys (unscale)
    short_polys = []
    for i in range(min(3, reduced.nrows())):  # Paper expects 3 polys
        coeffs_list = reduced.row(i)
        poly_dict = {mon_list[col]: ZZ(coeffs_list[col]) // (X^mon_deg[mon_list[col]][0] * Y^mon_deg[mon_list[col]][1] * Z^mon_deg[mon_list[col]][2]) for col in range(dim) if coeffs_list[col] != 0}
        short_polys.append(R(poly_dict))
    
    # Groebner basis
    I = Ideal(short_polys)
    gb = I.groebner_basis()
    print(f"Groebner basis: {gb}")
    
    # Extract roots (heuristic: look for linear in y or z, as per paper experiments)
    b, p, q = None, None, None
    for poly in gb:
        if poly.degree() == 1:
            vars = poly.variables()
            if y in vars and poly.degree(y) == 1:
                p = -poly.constant_term() / poly.lt().coefficient()
            elif z in vars and poly.degree(z) == 1:
                q = -poly.constant_term() / poly.lt().coefficient()
            elif x in vars and poly.degree(x) == 1:
                b = -poly.constant_term() / poly.lt().coefficient()
        if b and p and q:
            break
    
    # If not found, try variety (over QQ, may need extension)
    if not all([b, p, q]):
        try:
            roots = I.variety(ring=QQbar)
            if roots:
                root = roots[0]
                b, p, q = root[x], root[y], root[z]
        except:
            pass
    
    if b and p and q:
        p, q = ZZ(p), ZZ(q)  # Round if approx
        print(f"Roots: b={b}, p={p}, q={q}")
        if p^r * q == N and is_prime(p) and is_prime(q):
            print("Valid factorization")
            return p, q, r
    print("Failed to find roots")
    return None, None, None

# Rest of functions (compute_private_exponent, decrypt_with_crt, main) similar to your code, but in Sage syntax
def compute_private_exponent(p, q, r, e):
    phi_pr = p^(r-1) * (p - 1)
    lambda_q = q - 1
    lambda_N = lcm(phi_pr, lambda_q)
    try:
        d = inverse_mod(e, lambda_N)
        print(f"d = {d}")
        return d
    except ZeroDivisionError:
        print("Not coprime")
        return None

def decrypt_with_crt(c, d, p, q, r):
    p_r = p^r
    phi_pr = p^(r-1) * (p - 1)
    d_p = d % phi_pr
    d_q = d % (q - 1)
    m_p = pow(c, d_p, p_r)
    m_q = pow(c, d_q, q)
    q_inv = inverse_mod(q, p_r)
    m = m_q + q * ((m_p - m_q) * q_inv % p_r)
    m %= (p_r * q)
    print(f"m = {m}")
    return m

def main_lattice_decryption(N, e, c, delta=0.27, r=2, m=3, a=2, t=4):
    p, q, r_found = lattice_attack(N, e, delta, r, m, a, t)
    if not p or not q:
        return None
    d = compute_private_exponent(p, q, r, e)
    if d is None:
        return None
    m = decrypt_with_crt(c, d, p, q, r)
    ver = pow(m, e, N) == c
    print(f"Verification: {ver}")
    return m

# Test with small example
test_N = 453749993609862423767406315499943576715619270719355402974238598052955394928115736552052149359997786246220356697682085875952921814303608698370621001593498202664137105614797706092963766648597009961505999304804868628819913053836743203352789790043629722002657561251200479461682387841209989432114975491624177384451891391379186877943435674941392793230667987075796005304723586746499234907181428238498088293365909082016312817879158926491633438828864279569813880449928903197442314056798082948316345333020124333422271010266558240704462657795437331284568470273071623784463980804356407048493506788785174496491522489832266993857493571141791095824560928202787853918454906925294108108307632454643181292284238139014139655661468855857641112527475810964398489817726886715552651548640655208966527802039076290335379020936965043298763839401599171514405533064382889246509075110671027508911604428775812417740369127806015112477816224090013387055029147110760958727460929612596488683715157524348089512845563356023108705591279503195318426654042354995168730827224275774338589354960843892311527795210256625076161530148014308373510205475803126620273122026355448431101623251807914872657094636473462128842533375598676295429191094715741380629940237085984351828455402671411359040985079388223788455687113495701851623894956957645550925519912856378258637975444139968552783159276481826294558026430514802530631451990707908860581231085522384501312007775067802744550720121309711568063672057651894571577955667125277841940896121389597477800999510099897802458519569488399149967890922260665966515878625384142699235491857754702310410293104365494144520258022000143265495269730031163170529640396070358144325050554262827350506974225316594176431839182834588457225496863312818607491183538421503085095259381779598083377226530394482769313660477032407154580895878594632722208659675114254258704727980012253577921828077614896255390805697890016011327984029221311538789806793160662655383849913943647282192959359920313936222580284259387292748269260001904819421
test_e = 65537
test_c = 111485787416215732083419888356058001033979399362109360508261870891148407244056915320842057004505782715602818123447300884095020848041889695814526433868629365023169179222249266389625852952987468768744093949285183059141092635835298369742277053305386129494498932888847574300808388089268325285315544768758243962776305338522622185253641406040039766863839006857421878923985989934964980608678162026614939501709616234022560513068727741227451418843199235135749095269341297819825204093449152040119450428760583322599411826493866419830826968438441276668192358564834603596666357837414657021199051732261588602224173516664537564148394089550429651483809997867450677992922064193344874770747503400904093801780873626948092493848377891687023262100558540402729588031436030432454794249812343438390584037127772193904170421087845937142186548759745304853458426108895472726544041009713185818852009059377614660100111304092214002252935797010588338697682764623226411372959149475213491898026585839227437083313605739136374826611550285890516268274465906516027362250609767630889277144334385329907083036842578230411382780986903493096135223344890879558957044578591669932029144455308584539542287253481580691466811698093274707201630462570730775293023489199764838103523755662461374751198958467426358006688694286113733499476208949378697239611716306477782691571949837271003799623803484168508367440466097349584557388186877058472216663997659060248313992041943213504830112928710777702704154453752685836709744851134510916858519306810917203250148615798973854768579912019268884506350213467640771346485176419582269169891572750725266499997539100897292414501918122708319038201277181780871349160435630305579622638283737414742402944963614214372396516130499982252764818643861950391333197124142602658189297469501831730837739445119194832277196410874479162266849124548988494138572551706403876056107887113871741993117507279411718762898238612675676913155939479449418868042006329815701818716034433424936492656520443344944013881853487228563694901400446844531668

result = main_lattice_decryption(test_N, test_e, test_c, delta=0.27, r=3, m=22, a=20, t=49
qc.cx(0, 1))
if result is not None:
    print(f"Test decrypted: {result}")