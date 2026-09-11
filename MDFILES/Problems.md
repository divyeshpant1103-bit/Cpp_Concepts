The Problem: The Smart Coffee Maker
Question:
Create a class called CoffeeMaker that simulates a coffee machine at a local cafe. The class must keep track of its resources and the money it has made.
It should have three private data members:
waterLevel (type int, representing milliliters)
beanLevel (type int, representing grams)
totalCash (type double)
1. Constructor & Setup:
Create a constructor that initializes waterLevel to 1000, beanLevel to 500, and totalCash to 0.0. (Assume the machine starts completely full).
2. Member Functions:
Provide the following member functions:
makeEspresso(): An espresso requires 50ml of water and 18g of beans. If the machine has enough resources, deduct the water and beans, add $3.00 to totalCash, and print "Espresso is ready!". If it does not have enough resources, print "Error: Not enough water or beans." and do not change any values.
makeAmericano(): An Americano requires 150ml of water and 18g of beans. If it has enough resources, deduct them, add $4.50 to totalCash, and print "Americano is ready!". Otherwise, print the same error message.
restock(): Resets waterLevel back to 1000 and beanLevel back to 500.
report(): Prints the current amount of water, beans, and total cash collected.
3. Test Program:
Write a main() function with a while(true) loop (just like the TollBooth problem). Give the user a menu where they can press:
'E' to buy an Espress
'A' to buy an Americano
'R' to Restock the machine
'S' to Show the report
'Q' to Quit