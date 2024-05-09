#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;








 class Product { // base class product  
    protected:
    float price;
    string name;
    int quantity ;
    string type;
public: 

float getPrice(){ // used in the comparator to sort according to price
    return price;
}
string getName(){ // used in the comparator to sort according to name
    return name;
}
int getQuantity() { // used in the comparator to sort according to quantity
    return quantity;
}
bool operator==(const Product& other) const { // i have to overridde the == operator to use it 
                                             //for the comparators for the sort 
                                             //function because i am comparing user-defined data
        
        return name == other.name && price == other.price && quantity == other.quantity;  
    }
 void displayDetails(){
    cout<< "Name: "<< name<< " price: "<< price<< " quantity: "<< quantity<< " type: "<< type <<endl;
}
};
//========================================================================================================================
class ElectronicProducts : public Product { // first derived class from products base class
private: 
int warranty;
string factory;
public:
ElectronicProducts (int p, string n, int q, string t){ // constructor of elctronic products
    price=p;
    name=n;
    type=t;
    quantity=q; // num of devices available 
   
}
 void displayDetails(){ //overridden to display the warranty of electronic products
        cout<< "Name: "<< name<< " price: "<< price<< " quantity: "<< quantity<< " type: "<< type <<endl
        << "warranty "<< warranty<<" years "<<endl<< "factory: "<< factory<<endl;
}
};
//========================================================================================================================

class Foodproducts : public Product {
    private: 
  string expiryDate;
public:
  Foodproducts (int p, string n, int q, string t){ // constructor of food products
    price=p;
    name=n;
    type=t;
    quantity=q; // quantity
   
};
};
//========================================================================================================================
class  BookProducts: public Product{
private:
string author;
string genre ;
public:
  BookProducts(int p, string n, int q, string t){ // constructor of book products
 price=p;
    name=n;
    type=t;
    quantity=q; // quantity
    
}};
//========================================================================================================================
  template<class T> 
   class  ProductManger { 
    private:
     vector<T> products; // vector thats holds all products to manage

    public:
 static bool   priceComparator (  Product& a,  Product& b) { // custom comparator for price 
     return a.getPrice()<b.getPrice();

// they should be static to be able to access data without being an instance of the classes of the data accessed
    }

      static bool   quantatiyComparator (  Product& a,  Product& b) { // custom comparator for quantity
     return a.getQuantity()<b.getQuantity(); }
    static  bool   nameComparator (  Product& a,  Product& b)  { // custom comparator for name
     return a.getName()<b.getName();
    }  
    void addproducts ( const T& Product){ //  adding the products to the product vector
        products.push_back(Product);
        
    }
    typename vector<T>::iterator findfunction(const T& Product) { // find function to find the 
                                                             //index of the element ot remove
        return find(products.begin(), products.end(), Product);
    }

    void removeProduct(const T& Product) { // remove function
        auto it = findfunction(Product);
        if (it != products.end()) {
            products.erase(it);
        }
    }   
 void Sorts(const string sortBy) { //sorts function to sort products using a custom comparator
    if (sortBy == "Price" || sortBy == "price") {
        sort(products.begin(), products.end(), priceComparator);
    }
    else if (sortBy == "Name" || sortBy == "name") {
        sort(products.begin(), products.end(), nameComparator);
    }
    else if (sortBy == "Quantity" || sortBy == "quantity") {
        sort(products.begin(), products.end(), quantatiyComparator);
    }
}
  ProductManger<T> operator+(const T& product) const { //overload the + to add products
 ProductManger<T> manager = *this; // save the manager entered to a temp var to use to call the function
        manager.addproducts(product); // call the function
        return manager; //return the function because we declared its type as a productmanager
    
}
 friend  ostream& operator<<(ostream& os,  ProductManger<T>& manager)  {  //overload the << to display products products
        manager.displayProducts();
        return cout;
    }
void displayProducts()  { //function to display products
        for ( auto& product : products) {
            product.displayDetails();
        }
    }

    

};
//=========================================================================================================================
   
class Discounts {
    // class of discounts
private:
string Cname;
float value;


public:
Discounts(string n,float v){
    Cname=n;
    value=v;
}




string getCname(){
    return Cname;
}

float getValue(){
    return value;
}


};
//=========================================================================================================================
   

template<class T> 
   class  shoppingCarts { 
    private:
     vector<T> shoppingCarts;  // vector thats holds all products to put in a cart

     public:
     void addproducts ( const T& Product){ //  adding the products to the cart vector
        shoppingCarts.push_back(Product);
        
    }
    typename vector<T>::iterator findfunction(const T& Product) { // find function to find the 
                                                             //index of the element ot remove
        return find(shoppingCarts.begin(), shoppingCarts.end(), Product);
    }

    void removeProduct(const T& Product) { // remove function
        auto it = findfunction(Product);
        if (it != shoppingCarts.end()) {
            shoppingCarts.erase(it);
        }
    }   
    
   vector<T> getProducts() { // used in the order constructor to fill 
                            //the order vector with the shoping cart vector
        return shoppingCarts;
    }
    void printCart()  {
      
        cout << "Products in the cart:" << endl;
        for ( auto& product : shoppingCarts) {
            cout << "Name: " << product.getName() << ", Price: " << product.getPrice() <<  endl;
        }
        cout << "-----------------------" << endl;
    }

   };
//=========================================================================================================================

class Orders  {
    private :
    int orderId;
    int allOrders=0;
    float orderPrice=0;

    
     vector<Discounts> coupons; // vector that takes the discounts to be applied on the order
    vector<Product>  cart; // vector that takes a type object of class product and declares an //
                               //array to store products to be ordered
    public:
    Orders(int ordernum,  shoppingCarts<Product>& shop ){ // order constructor takes a vector object of /
                                                        //shopping cart gives it an Id and intializes the order
        cart=shop.getProducts();
        orderId=ordernum;
        
        allOrders++;

    }



 friend Orders operator-( Orders& order, const Discounts& discount) {
    
    order.addCoupon(discount);
    return order;


}
   int calculatePrice(){ // function to calculate total  price 
    for ( auto& product : cart) {
            orderPrice+=product.getPrice();
        }
     
        cout<< "Total price: "<< orderPrice<<endl;
        
        return orderPrice;

    
   }
    
void addCoupon( Discounts a){
     
        if( coupons.empty()){
            coupons.push_back(a);
            if (a.getCname() == "percentage OFF"){
                calculatePrice();
           orderPrice*=a.getValue() ; // Calculate the discount rate (1 - percentage)



            }
            else
         if(a.getCname() == "-$"){
                orderPrice=calculatePrice();
           orderPrice-=a.getValue() ;
            }
           
           
        }
        else{
        cout<< "you have already used a coupon on this order \n u can only use 1 coupon per order\n";
        }
    }
   
   void printOrder()  { //function to display the order
      cout << "Order ID: " << orderId << endl;
        cout << "Products in the order:" << endl;
        for ( auto& product : cart) {
            cout << "Name: " << product.getName() << ", Price: " << product.getPrice() <<  endl;
        }
        
        cout<<endl<< "Total price after discounts : "<< orderPrice <<endl;
        cout << "-----------------------" << endl;
         
    }
    
   
    int getId(){ return orderId;}
    int getall(){ return allOrders;}
    

   };
   //=========================================================================================================================
ProductManger <ElectronicProducts> ElectronicManager; 
ProductManger<Foodproducts> Foodmanager;
ProductManger<BookProducts> bookmanager;



class   Admin {

private:
string username;
string password;
string name;
int id ;
int p;
string na;
int q;
string t;

public:
Admin(string u, string p, string n, int i){
username=u;
password=p;
name=n;
id=i;

}



void createProduct(int type , string name){
     cout<< "enter the price \n";
    cin>> p;
    cout<< "enter the nsme \n";
    cin>> na;
    cout<< "enter the quantity \n";
    cin>> q;
    cout<< "enter the type \n";
    cin>> t;

if (type== 1){

ElectronicProducts name (p,na,q,t);
ElectronicManager.addproducts(name);

} 
else if ( type== 2){
    Foodproducts name (p,na,q,t);
Foodmanager.addproducts(name);
}
else if ( type== 3){
    BookProducts name (p,na,q,t);
    bookmanager.addproducts(name);
    
}


}

// void removeProduct (){
// string productName;
// int type;



// cout<< "enter product name";
//      cin>> productName ;
//      cout<< "enter product type";
//      cin>> type ;
//     if (type== 1){

// ElectronicProducts name (p,na,q,t);
// ElectronicManager.removeProduct(productName);

// } 
// else if ( type== 2){
//     Foodproducts name (p,na,q,t);

// }
// else if ( type== 3){
//     BookProducts name (p,na,q,t);
    
// }
    
// }



};























//=========================================================================================================================

int main(){
    
    
    ElectronicProducts E1(21,"LAPTOP",31,"dell");//product 1
    ElectronicProducts E2(32,"PHONE",32,"Iphone");//product 2
    Foodproducts f1(34,"tuna can",34," canned food" );//product 3
    BookProducts b1 (68, "great gatsby", 700, "book");//product 4
   BookProducts b2 (64, "ard el nefaq", 400, "book");//product 5


   
   ElectronicManager=ElectronicManager+E1; // adding the products to the manager
   ElectronicManager=ElectronicManager+E2; // adding the products to the manager
//    cout<<ElectronicManager;
  

   //cout<<ElectronicManager;// overridden the << operator to display the manager
   ElectronicManager.removeProduct(E1);// removing the products to the manager
   
//    ElectronicManager=ElectronicManager+E1;// adding the products to the manager
//    cout<<ElectronicManager;// overridden the << operator to display the manager
   
    
ElectronicManager.Sorts("quantity");//sorting the manager
// overridden the << operator to display the manager
//cout<<"=====================================";


bookmanager.addproducts(b1);// adding the products to the manager
bookmanager.addproducts(b2);// adding the products to the manager
//cout<<bookmanager;// overridden the << operator to display the manager

 bookmanager.Sorts("name");//sorting the manager
 //cout<<bookmanager;// overridden the << operator to display the manager
 
 

Foodmanager=Foodmanager+f1;// adding the products to the manager
//cout<< Foodmanager;// overridden the << operator to display the manager



shoppingCarts <Product> cart1;// creating a cart 
shoppingCarts <Product> cart2;// creating a cart 
shoppingCarts <Product> cart3;// creating a cart 
cart1.addproducts(b1);// adding the products to the cart
cart1.addproducts(E1);// adding the products to the cart
cart1.removeProduct(b1);
cart1.printCart();//displaying the cart
cart2.addproducts(E2);// adding the products to the cart
cart2.addproducts(f1);// adding the products to the cart
cart2.printCart();//displaying the cart
cout<<"=====================================";

cart3.addproducts(b2);// adding the products to the cart
cart3.printCart();//displaying the cart


Discounts A ("percentage OFF",0.9); //creating coupons
Discounts B ("-$",10);//creating coupons
Discounts c ("percentage OFF",0.6);//creating coupons
Discounts d ("-$",30);//creating coupons



//Admin a1 ("admin1", "admin1","admin1",0);
//a1.createProduct(1,"laptop");
ElectronicManager.displayProducts();



Orders order1 (1 ,cart1);//creating an order

order1=order1-A; //applying the coupon by the overridden operator -
order1.printOrder();//printing the order





Orders order2 (2 ,cart2);//creating an order
order2.addCoupon(c);//applying the coupon 
order2.printOrder();//printing the order



    return 0;}