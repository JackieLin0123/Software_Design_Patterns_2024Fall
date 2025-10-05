class Employee {
private:
    int typeCode;  

public:
    Employee(int typeCode) : typeCode(typeCode) {}

    int getTypeCode() const {
        return typeCode;
    }

    void printEmployeeInfo() const {
        if (typeCode == 1) {
            cout << "This is a Manager" << endl;
        } else if (typeCode == 2) {
            cout << "This is a Technical Employee" << endl;
        } else if (typeCode == 3) {
            cout << "This is a Sales Employee" << endl;
        }
    }
};

int main() {
    Employee emp1(1);  
    Employee emp2(2);  
    Employee emp3(3);  

    emp1.printEmployeeInfo();
    emp2.printEmployeeInfo();
    emp3.printEmployeeInfo();

    return 0;
}

class Employee {
private:
    int typeCode;  

public:
    Employee(int typeCode) : typeCode(typeCode) {}

    int getTypeCode() const {
        return typeCode;
    }

    virtual void printEmployeeInfo() const {
        if (getTypeCode() == 1) {
            cout << "This is a Manager" << endl;
        } else if (getTypeCode() == 2) {
            cout << "This is a Technical Employee" << endl;
        } else if (getTypeCode() == 3) {
            cout << "This is a Sales Employee" << endl;
        }
    }
};

class Employee {
private:
    int typeCode;  

    Employee(int typeCode) : typeCode(typeCode) {}

public:
    static Employee* createEmployee(int typeCode) {
        if (typeCode == 1) {
            return new Manager();
        } else if (typeCode == 2) {
            return new TechnicalEmployee();
        } else if (typeCode == 3) {
            return new SalesEmployee();
        }
        return nullptr;
    }

    int getTypeCode() const {
        return typeCode;
    }

    virtual void printEmployeeInfo() const = 0;
};

class Manager : public Employee {
public:
    Manager() : Employee(1) {}

    void printEmployeeInfo() const override {
        cout << "This is a Manager" << endl;
    }
};


class TechnicalEmployee : public Employee {
public:
    TechnicalEmployee() : Employee(2) {}

    void printEmployeeInfo() const override {
        cout << "This is a Technical Employee" << endl;
    }
};

class SalesEmployee : public Employee {
public:
    SalesEmployee() : Employee(3) {}

    void printEmployeeInfo() const override {
        cout << "This is a Sales Employee" << endl;
    }
};

class Payment {
public:
    static const int CREDIT_CARD = 1;
    static const int PAYPAL = 2;
    static const int BANK_TRANSFER = 3;

private:
    int paymentType; 

public:
    explicit Payment(int type) : paymentType(type) {}

    void setPaymentType(int type) {
        paymentType = type;
    }

    double calculateFee(double amount) const {
        switch (paymentType) {
            case CREDIT_CARD:
                return amount * 0.02;
            case PAYPAL:
                return amount * 0.03;
            case BANK_TRANSFER:
                return 5.0;
            default:
                throw std::invalid_argument("Invalid payment type");
        }
    }
};

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual double calculateFee(double amount) const = 0;
};

class CreditCardPayment : public PaymentStrategy {
public:
    double calculateFee(double amount) const override {
        return amount * 0.02;
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    double calculateFee(double amount) const override {
        return amount * 0.03;
    }
};

class BankTransferPayment : public PaymentStrategy {
public:
    double calculateFee(double amount) const override {
        return 5.0; 
    }
};

class Payment {
private:
    std::unique_ptr<PaymentStrategy> paymentStrategy;
public:
    Payment(std::unique_ptr<PaymentStrategy> strategy) : paymentStrategy(std::move(strategy)) {}

    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy) {
        paymentStrategy = std::move(strategy);
    }

    double calculateFee(double amount) const {
        return paymentStrategy->calculateFee(amount);
    }
};

int main() {
    Payment payment(std::make_unique<CreditCardPayment>());
    double amount = 1000.0;

    std::cout << "Credit Card Fee: " << payment.calculateFee(amount) << std::endl;

    payment.setPaymentStrategy(std::make_unique<PayPalPayment>());
    std::cout << "PayPal Fee: " << payment.calculateFee(amount) << std::endl;

    payment.setPaymentStrategy(std::make_unique<BankTransferPayment>());
    std::cout << "Bank Transfer Fee: " << payment.calculateFee(amount) << std::endl;
    return 0;
}

Credit Card Fee: 20  
PayPal Fee: 30  
Bank Transfer Fee: 5