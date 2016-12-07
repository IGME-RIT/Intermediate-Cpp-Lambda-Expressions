/*
Lambda Expressions
(c) 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// Lambda Expressions are a cool feature of C++ that serve as a short hand for functors.
// With functors, you can create objects that are treated as functions, and pass them as parameters, or store them as variables.
// Lambdas enable use to do this without defining a class for our functor.


// Before we start, define a template function that takes in a generic type (that overrides (), acting as a functor).
template<class op>
int operation(int a, int b, op func)
{
    int result = func(a, b); // The functor will take in 2 ints, and then return another int
    cout << result << endl;
    return result;
}


int main() 
{   
    {
        // The first thing we'll do is test out our template function with a functor class to see if it works.
        struct printFunctor
        {
            int operator()(int a, int b) const  // The function operator is overriden to just print out the input.
            {
                cout << a << " " << b << endl;
                return 0;                       // return 0.
            }
        };

        // Call printFunctor on 2 and 3, then print out the return value.

        cout << "calling functor with template function:" << endl;
        printFunctor p;
        operation(2, 3, p);

        cin.get();
    }



    {
        // The fact that we can do that at all is awesome, but there's a lot of code involved in making an functor class.
        // Lambdas allow us to do the same thing without the extra cluttering up our code:

        // Instead of defining a class, we just create the object immediately, and the compiler makes the class for us.
        // First we use auto for the type of our object, (because the functor we are creating has "no type". (the type is created by the compiler)
        auto addition = [](int a, int b)   // The [] identifies this as a lambda function. It's called the capture clause, but we don't need it here.
        {                                   // After the [], we can define the function very similarly to how we would define any other function.
            return a + b;
        };

        // Now, we just call the function.
        cout << "calling lambda defined function:" << endl;
        addition(2, 3);
        cout << "passing lambda defined function into template function to be called:" << endl;
        operation(2, 3, addition);


        cin.get();
    }
    



    {

        // Since the function being defined is just an object, it's possible to call the funciton inline as you create it:
        int larger = [] (int a, int b) { return a > b ? a : b; } (2, 3);
        cout << "larger of 2 and 3: " << larger << endl;

        // The capture clause allows you to pass variables into the functor when it's created (similar to a functor constructor)
        int two = 2;
        auto lessThan2 = [a = two] (int b) { return a < b ? a : b; };   // You can pass in multiple things separated by commas, ie [a = 1, b = 2, c = 3]
        int smaller =  lessThan2(3);                                    // There are other more complcated things that can be done with the capture clause.
        cout << "smaller of 2 and 3: " << smaller << endl;


        int thing;
        cout << "thing: " << thing << endl;
        auto setThing = [&a = thing](int b) { a = b; };                 // You can use references inside the capture clause too!
        setThing(2);
        cout << "thing: " << thing << endl;


        cin.get();
    }




    {
        // There are a couple of other cool things we can do with our lambda expressions:

        // auto is not technically required for storing lambda functions
        // The standard library provides the type function (#include <functional>), which is a template class that stores functor types.
        function<int(int, int)> multiply = [] (int a, int b) { return a * b; };

        // All you need is the type of the function. In this case it's int(int, int)
        // This is helpful for passing functors around, but adds an extra layer of abstraction that you might not want.
        cout << "multiply(2, 3): " << multiply(2, 3) << endl;




        // The standard library also provides some really cool functions #include <algorithm>
        
        // Let's create a vector of integers:
        vector<int> numbers({ 2, 5, 17, 99, 33, -6 }); // Construct vector from an array (a useful feature of vector)

        // This functor returns whether or not a number is larger than 10.
        auto greaterThan10 = [] (int other) { return other > 10; };

        // The count_if function counts the number of elements in a collection (that pass a test) with an iterator.
        // We just need to give it a beginning position, and end position, and a functor which is used to test the value passed in.
        int total = count_if(numbers.begin(), numbers.end(), greaterThan10);
        
        cout << "numbers in array greater than 10" << total << endl;

        
        // If these functions are interesting to you, check out the algorithm header. It includes all kinds of functions like this.
        cin.get();
    }



    return 0;   // End Program.
}