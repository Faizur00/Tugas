public class main{
  public static void main(String[] args) {
    sarjana Faiz = new sarjana();
    Faiz.setName("Ahmad Faizur Rahman");
    Faiz.setNim("D121241107");
    Faiz.setProdi("Informatika");
    Faiz.setIpk(2);
    Faiz.setKonsentrasi("AI/ML");

    Faiz.tampilkanData();

    System.out.println("================================"); 

    pasca FaizP = new pasca();
    FaizP.setName("Faizur Rahman");
    FaizP.setNim("D121241107");
    FaizP.setProdi("Informatika");
    FaizP.setIpk(2);
    FaizP.setThesis("Judul Thesis");

    FaizP.tampilkanData();

    System.out.println("================================"); 

    pertukaran FaizPer = new pertukaran();
    FaizPer.setName("Faizur");
    FaizPer.setNim("D121241107");
    FaizPer.setProdi("Informatika");
    FaizPer.setIpk(2);
    FaizPer.setAsal("Makassar");

    FaizPer.tampilkanData();
  }
}
