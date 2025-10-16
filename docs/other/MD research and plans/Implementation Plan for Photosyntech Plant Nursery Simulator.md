
---

### **Phase 1: Foundation & Core Entities (Week 1-2)**

#### **Step 1: Project Setup**

1. Create C++ project structure
2. Set up header (.h) and implementation (.cpp) file organization
3. Create main folders: `/src/plants`, `/src/patterns`, `/src/staff`, `/src/sales`, `/src/gui`
4. Set up Makefile/CMakeLists.txt
5. Initialize version control (Git)

#### **Step 2: Define Enums & Basic Types**

Create fundamental enumerations:

```cpp
enum class PlantType { TREE, SHRUB, FLOWER, SUCCULENT };
enum class Season { SPRING, SUMMER, AUTUMN, WINTER };
enum class SoilType { LOAMY, SANDY, CLAY, PEATY };
```

#### **Step 3: Implement Strategy Pattern - Plant Care**

**Priority: HIGH** (Required for FR3, FR4)

1. **Create WaterStrategy hierarchy:**
    
    - `WaterStrategy` (abstract interface)
    - `HighWaterStrategy`, `MediumWaterStrategy`, `LowWaterStrategy`
2. **Create SunStrategy hierarchy:**
    
    - `SunStrategy` (abstract interface)
    - `FullSunStrategy`, `PartialSunStrategy`, `ShadeStrategy`
3. **Test strategies independently** before integration
    

---

### **Phase 2: Plant Core with State Pattern (Week 2-3)**

#### **Step 4: Implement State Pattern - Maturity States**

**Priority: HIGH** (Required for FR5)

1. **Create MaturityState hierarchy:**
    
    - `MaturityState` (abstract interface)
    - `SeedState`, `MidGrowthState`, `MatureState`, `DeadState`
2. **Implement state-specific behaviors:**
    
    - Growth rates
    - Price modifiers
    - Availability for sale
3. **Implement state transitions** based on age
    

#### **Step 5: Create Base Plant Class**

**Priority: CRITICAL** (Core entity)

1. **Define Plant class with all attributes:**
    
    ```cpp
    class Plant {
        PlantType type;
        Season season;
        string name;
        int age;
        double growthRate;
        WaterStrategy* waterStrategy;
        SunStrategy* sunStrategy;
        MaturityState* currentState;
        // ... other attributes
    }
    ```
    
2. **Implement basic plant methods:**
    
    - `water()`, `grow()`, `getPrice()`, `getInfo()`
3. **Test Plant with different strategies and states**
    

---

### **Phase 3: Creational Patterns (Week 3-4)**

#### **Step 6: Implement Builder Pattern**

**Priority: CRITICAL** (Required for FR1, FR2)

1. **Create PlantBuilder class** with fluent interface:
    
    ```cpp
    PlantBuilder& setType(PlantType)
    PlantBuilder& setSeason(Season)
    PlantBuilder& setWaterStrategy(WaterStrategy*)
    Plant* build()
    ```
    
2. **Add validation logic** in `build()` method
    
3. **Create convenience methods** for common configurations
    
4. **Test builder with various combinations**
    

#### **Step 7: Implement Prototype Pattern**

**Priority: HIGH** (Required for FR3)

1. **Add `clone()` method** to Plant class
2. **Implement deep copy** of all attributes
3. **Test cloning** with different plant configurations
4. **Verify independence** of clones

#### **Step 8: Implement Singleton - Inventory**

**Priority: HIGH** (Required for FR7)

1. **Create Inventory singleton:**
    
    - Private constructor
    - `getInstance()` static method
    - Delete copy constructor and assignment operator
2. **Add basic inventory methods:**
    
    - `addPlant()`, `removePlant()`, `getPlantCount()`

---

### **Phase 4: Structural Patterns - Organization (Week 4-5)**

#### **Step 9: Implement Composite Pattern**

**Priority: HIGH** (Required for FR6)

1. **Create PlantComponent interface:**
    
    ```cpp
    class PlantComponent {
        virtual void add(PlantComponent*) = 0;
        virtual void remove(PlantComponent*) = 0;
        virtual int getCount() = 0;
    }
    ```
    
2. **Implement Leaf (Plant)** - individual plant behavior
    
3. **Implement Composite (PlantCollection, Stock)** - group behaviors
    
4. **Integrate with Inventory** for hierarchical storage
    
5. **Test tree structure** operations
    

#### **Step 10: Implement Decorator Pattern**

**Priority: MEDIUM** (Required for FR11)

1. **Create PlantDecorator abstract class:**
    
    ```cpp
    class PlantDecorator : public Plant {
        Plant* wrappedPlant;
    }
    ```
    
2. **Implement concrete decorators:**
    
    - `PotDecoration`
    - `GiftWrapDecoration`
    - `CarePackageDecoration`
3. **Override `getPrice()` and `getDescription()`**
    
4. **Test decorator stacking**
    

---

### **Phase 5: Observer Pattern - Notifications (Week 5-6)**

#### **Step 11: Implement Observer Pattern**

**Priority: HIGH** (Required for FR8, FR9)

1. **Create Observer interface:**
    
    ```cpp
    class Observer {
        virtual void update() = 0;
    }
    ```
    
2. **Make Plant and Inventory as Subjects:**
    
    - `attach(Observer*)`, `detach(Observer*)`, `notify()`
3. **Create Staff as Observer:**
    
    - Implement `update()` method
    - Handle plant state changes
    - Handle inventory changes
4. **Test notifications** for various events
    

---

### **Phase 6: Staff & Interaction Patterns (Week 6-7)**

#### **Step 12: Create Staff Classes**

**Priority: MEDIUM**

1. **Define Staff hierarchy:**
    
    - Base `Staff` class (implements Observer)
    - `Gardener`, `SalesStaff` subclasses
2. **Implement staff operations:**
    
    - Plant care tasks
    - Customer assistance
    - Inventory monitoring

#### **Step 13: Implement Mediator Pattern**

**Priority: HIGH** (Required for FR10)

1. **Create Mediator interface**
    
2. **Implement SalesFloor as ConcreteMediator:**
    
    - `requestAssistance(Customer*)`
    - `assignStaff(Customer*, Staff*)`
    - `completeTransaction()`
3. **Create Customer class** as Colleague
    
4. **Test staff-customer coordination**
    

---

### **Phase 7: Traversal & Commands (Week 7-8)**

#### **Step 14: Implement Iterator Pattern**

**Priority: MEDIUM** (Required for FR12)

1. **Create Iterator interface:**
    
    ```cpp
    class Iterator {
        virtual void first() = 0;
        virtual void next() = 0;
        virtual bool isDone() = 0;
        virtual Plant* currentItem() = 0;
    }
    ```
    
2. **Implement concrete iterators:**
    
    - `SpringIterator`, `SummerIterator`, `AutumnIterator`, `WinterIterator`
    - `MatureIterator` (sale-ready plants)
3. **Add `createIterator()` to Aggregate**
    
4. **Test seasonal browsing**
    

#### **Step 15: Implement Command Pattern**

**Priority: HIGH** (Required for FR13)

1. **Create Command interface:**
    
    ```cpp
    class Command {
        virtual void execute() = 0;
    }
    ```
    
2. **Implement concrete commands:**
    
    - `PurchasePlantCommand`
    - `WaterPlantCommand`
    - `AddToInventoryCommand`
    - `BrowsePlantsCommand`
3. **Create Invoker (GUIController)**
    
4. **Test command execution and queuing**
    

---

### **Phase 8: Facade & Integration (Week 8-9)**

#### **Step 16: Implement Facade Pattern**

**Priority: HIGH** (Required for FR14)

1. **Create NurseryFacade class:**
    
    ```cpp
    class NurseryFacade {
        Inventory* inventory;
        StaffManager* staffManager;
        SalesFloor* salesFloor;
    public:
        void purchasePlant(Plant*, Customer*);
        void waterPlant(Plant*, Staff*);
        void addStock(int quantity, PlantBuilder);
        vector<Plant*> browsePlants(Season);
    }
    ```
    
2. **Coordinate all subsystem interactions**
    
3. **Simplify complex operations** for GUI
    
4. **Test facade methods** end-to-end
    

---

### **Phase 9: GUI Layer (Week 9-10)**

#### **Step 17: Implement GUI with Dear ImGui**

**Priority: MEDIUM**

1. **Set up Dear ImGui** framework
    
2. **Create main GUI windows:**
    
    - Inventory view
    - Plant browsing (with seasonal filtering)
    - Staff management
    - Transaction processing
3. **Connect GUI to Facade** via Commands
    
4. **Implement visual feedback** for observer notifications
    
5. **Add menu system** with clear navigation
    

---

### **Phase 10: Testing & Refinement (Week 10-11)**

#### **Step 18: Unit Testing**

1. **Test each pattern independently:**
    
    - Strategy switching
    - State transitions
    - Observer notifications
    - Builder validation
    - Prototype cloning
    - Decorator stacking
2. **Create test data sets:**
    
    - Various plant configurations
    - Different scenarios (purchase, growth, care)

#### **Step 19: Integration Testing**

1. **Test subsystem interactions:**
    
    - Purchase flow
    - Plant care routines
    - Inventory updates
    - Staff notifications
2. **Test performance requirements:**
    
    - 10,000 plant simulation (NFR1)
    - 5,000 plant inventory (NFR4)

#### **Step 20: Extensibility Testing**

1. **Add new plant season** (e.g., Rainy) - verify NFR2
2. **Add new care strategy** (e.g., Fertilizer)
3. **Add new decoration** (e.g., Ribbon)
4. **Verify changes limited to 2 files** per requirement

---

### **Phase 11: Documentation & Finalization (Week 11-12)**

#### **Step 21: Code Documentation**

1. **Add Doxygen comments** to all classes
    
2. **Create UML diagrams** in Visual Paradigm:
    
    - Class diagrams for each pattern
    - Sequence diagrams for key operations
    - Component diagram for architecture
3. **Write README** with:
    
    - Build instructions
    - Usage guide
    - Design pattern explanations

#### **Step 22: User Manual**

1. **Create text-based user guide**
2. **Document all available commands**
3. **Provide usage examples**
4. **Ensure NFR3 compliance** (usability)

---

## **Critical Success Factors**

### **Pattern Implementation Priority:**

1. ✅ **CRITICAL:** Builder, Singleton, State, Strategy (core functionality)
2. ✅ **HIGH:** Observer, Mediator, Composite, Facade, Prototype (integration)
3. ✅ **MEDIUM:** Iterator, Decorator, Command (features)

### **Testing Checkpoints:**

- After each pattern implementation
- After each subsystem completion
- Before GUI integration
- Final integration testing

### **Code Quality Standards:**

- Memory leak checks (valgrind)
- SOLID principles adherence
- Proper const correctness
- Smart pointer usage where appropriate

---

## **Estimated Timeline: 12 Weeks**

- **Weeks 1-3:** Foundation (Phases 1-2)
- **Weeks 4-6:** Core Patterns (Phases 3-5)
- **Weeks 7-9:** Advanced Features (Phases 6-8)
- **Weeks 10-12:** GUI, Testing, Documentation (Phases 9-11)

---

## **Risk Mitigation:**

1. **Pattern Integration Complexity:** Implement and test each pattern independently first
2. **Memory Management:** Use smart pointers early, avoid raw pointer juggling
3. **Observer Performance:** Optimize notification system for 10,000 plants
4. **GUI Learning Curve:** Start GUI work early, use simple layouts initially

This implementation plan builds systematically from foundational patterns to complex integrations, ensuring each component is tested before moving forward. Would you like me to elaborate on any specific phase or create implementation templates for any of the patterns?