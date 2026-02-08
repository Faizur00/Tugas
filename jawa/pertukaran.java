public class pertukaran extends mahasiswa {
    private String asal;

    public void setAsal(String asal) {
        this.asal = asal;
    }

    public void getAsal() {
       System.out.println(this.asal); 
    }

    @Override
    public void tampilkanData() {
        super.tampilkanData();{
            this.getAsal();
        }
    } 

}