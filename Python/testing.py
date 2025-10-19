


def hukum_mim_sukun(huruf):

    hukum_mim_sukun ={
        'م': 'Idgham Mutamasilain',
        'ب': 'Ikhfa Syafawi',
    }

    for mim_bertemu, cara_baca in hukum_mim_sukun.items():
        if mim_bertemu == 'م':
            print(cara_baca)
        elif mim_bertemu == 'ب':
            print(cara_baca)
        else:
            print("Idzhar Syafawi")


def main():
    huruf = input("Masukkan huruf: ")
    hukum_mim_sukun(huruf)


if __name__ == "__main__":
    main()
        