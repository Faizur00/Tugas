public class mahasiswa {
    private String nim;
    private String name;
    private String prodi;
    private float ipk;


    public void setName(String name) {
        this.name = name;
    }

    public void getName() {
        System.out.println(this.name);
    }


    public void setNim(String nim) {
        this.nim = nim;
    }

    public void getNim() {
        System.out.println(this.nim);
    }


    public void setProdi(String prodi) {
        this.prodi = prodi;
    }

    public void getProdi() {
        System.out.println(this.prodi);
    }

    public void setIpk(float ipk) {
        this.ipk = ipk;
    }

    public void getIpk() {
        System.out.println(this.ipk);
    }   

    public void tampilkanData() {
        this.getName();
        this.getNim();
        this.getProdi();
        this.getIpk();
    }
    
    public mahasiswa(){
        super();
    }
}