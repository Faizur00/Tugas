public class inheritance {
    public static class Car { 
        String brand;
        String model;
        int year;
        
        public void setBrand(String brand) {
            this.brand = brand;
        }
        
        public String getBrand() {
            return this.brand;
        }
        
        public void setModel(String model) {
            this.model = model;
        }
        
        public String getModel() {
            return this.model;
        }
        
        public void setYear(int year) {
            this.year = year;
        }
        
        public int getYear() {
            return this.year;
        }
        
        public void displayInfo() {
            System.out.println("Brand: " + brand);
            System.out.println("Model: " + model);
            System.out.println("Year: " + year);
        }
    }
    
    public static void main(String[] args) {
        Car  myCar = new Car();
        myCar.setBrand("Toyota");
        myCar.setModel("Avanza");
        myCar.setYear(2023);
        
        System.out.println("Car Brand: " + myCar.getBrand());
        System.out.println("Car Model: " + myCar.getModel());
        System.out.println("Car Year: " + myCar.getYear())
    }
}
