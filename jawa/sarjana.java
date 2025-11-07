public class sarjana extends mahasiswa {
    private String konsentrasi;

    public void setKonsentrasi(String konsentrasi) {
        this.konsentrasi = konsentrasi;
    }

    public void getKonsentrasi() {
       System.out.println(this.konsentrasi); 
    }

    @Override
    public void tampilkanData()
    {
        super.tampilkanData();
        {
            this.getKonsentrasi();
        }
    } 
}