public class pasca extends mahasiswa {
    private String thesis;

    public void setThesis(String thesis) {
        this.thesis = thesis;
    }

    public void getThesis() {
       System.out.println(this.thesis); 
    }

    
    @Override
    public void tampilkanData()
    {
        super.tampilkanData();
        {
            this.getThesis();
        }
    } 
}