
#include <stack>
#include <iostream>
#include <string>
using namespace std;
int  CheckPrecdence( string ch)           // this function is for precedence check
{
    
    if (ch[0] == '*')
    {
        return 2;
    }
    else if (ch[0] == '/')
    {
        return 3;
    }
    else if (ch[0] == '+' || ch[0] == '-')
        return 1;
    else
        return 0;
}

void MutlidigitsExpressionAdjust( string exp, string Tempexp[], int& sizecounter)  // this fucntion adjusts for multiple digit values
{
    int Data[25] = {};
    int count = 0,j=0,a=0,flag=0;
    int Combined = 0;
    string ch=" ";
    for (int i = 0; i < exp.length(); i++)
    {
        ch = " ";
        if (exp[i] == '-')
        {
            if (i == 0 || ((exp[i+1]!='(' && exp[i+1] != ')') && (exp[i-1]=='*' || exp[i-1]=='-'|| exp[i-1]=='/' || exp[i-1]=='(')) && ((exp[i + 1] != '*' && exp[i + 1] != '/' && exp[i + 1] != '+' && exp[i + 1] != '(' && exp[i + 1] != ')')))
            {        i++;
                while (exp[i] !='*' && exp[i] != '-' && exp[i] != '/' && exp[i] != '+' && exp[i] != '(' && exp[i] != ')')
                {
                    ch = exp[i];
                    Data[count] = stoi(ch);
                    count++;
                    i++;
                }
                for (int j = 0; j < count; j++) {
                    Combined = Combined * 10 + Data[j]; // forming a number here
                }
                Combined = -Combined;
                Tempexp[a] = to_string(Combined); // storing it in a temp string
                sizecounter++;
                a++;
                i--;
                while (count >= 0) {  // emptying the data container for again use
                    Data[count] = 0;
                    count--;
                }


            }

            else if (exp[i] == '-' && exp[i+1]=='(') 
            {
                Tempexp[a] = exp[i];
                a++;
                sizecounter++;

            }
            else
            {
                Tempexp[a] = exp[i];
                a++;
                sizecounter++;
            }
            
            
            
        }
        else if (exp[i] == '*' || exp[i] == '/' || exp[i] == '+' || exp[i] == '(' || exp[i] == ')')
        {
            Tempexp[a] = exp[i];
            a++;
            sizecounter++;
        }
        else if (isdigit(exp[i])) {
            while ( (exp[i] != '*' && exp[i] != '-' && exp[i] != '/' && exp[i] != '+' && exp[i] != '(' && exp[i] != ')') && i < exp.length())
            {
                ch = exp[i];
                Data[count] = stoi(ch);
                count++;
                i++;
            }
            for (int j = 0; j < count; j++) {
                Combined = Combined * 10 + Data[j];
            }
            while (count >= 0) {
                Data[count] = 0;
                count--;
            }
            Tempexp[a] = to_string(Combined);
            sizecounter++;
            a++;
            i--;

        }
        Combined = 0;
        count = 0;
    }


   
    
}

bool InputValidation(const std::string& Exp)
{
    int flag = 0;
    // check 1


    for (int i = 0; i < Exp.length(); i++)
    {
        if ((Exp[i] >= 'A' && Exp[i] <= 'Z') || (Exp[i] >= 'a' && Exp[i] <= 'z'))
        {
            return false;
        }
    }


    for (int i = 0; i < Exp.length(); i++)
    {
        if (Exp[i] == '*' || Exp[i] == '/' || Exp[i] == '+'  )
        {   
            if (i == 0)
            {
                return false;      // returning false if any operator is found at start of expression
            }
            if (i == Exp.length() - 1)
            {
                return false;   // returning false if any operator is found at end of expression
            }
            if (i + 1 < Exp.length())
            {
                if (Exp[i + 1] == '*' || Exp[i + 1] == '/' || Exp[i + 1] == '+')
                {
                    return false;  // returning false if two operators are found together
                }
            }
            
        }
        if (Exp[i] == '(')
        {
            flag = 0;
            int j = i+1;
            if (Exp[j] == ')')
            {   
                return false; // returning false if opening closing brackets come together 
            }
            j++;
            while (j < Exp.length())
            {
                
                if (Exp[j] == ')')
                {
                    flag = 1;
                    break;
                }
                j++;
            }
            if (flag == 0)
            {
                return false;
            }
           
        }

        if (Exp[i] == ')')
        {
            flag = 0;
            int j = i - 1;
            if (Exp[j] == '(')
            {
                return false; // returning false if opening closing brackets come together 
            }
            j--;
            while (j >= 0)
            {

                if (Exp[j] == '(')
                {
                    flag = 1;
                    break;
                }
                j--;
            }
            if (flag == 0)
            {
                return false;
            }

        }
        
        

    }
    return true;
    
}

void Calculation(string Expression[], int ExpressionSizeCounter,stack<string> &Inputstack, stack<string> &OutputStack) // after the expression is converted into postfix notation, this now performs the calculation
{
    string ch;

    for (int i = 0; i < ExpressionSizeCounter; i++)
    {
        ch = ' ';
        if (Expression[i] == "*" || Expression[i] == "/" || Expression[i] == "+" || Expression[i] == "-")
        {

            ch = Expression[i];
            if (Inputstack.size() != 0)
            {
                for (int j = 0; Inputstack.size() != 0 && CheckPrecdence(ch) < CheckPrecdence(Inputstack.top()); )
                {
                    string temp = Inputstack.top();
                    OutputStack.push(temp);
                    Inputstack.pop();
                }
            }
            Inputstack.push(ch);


        }
        else if ((Expression[i] != ")" && Expression[i] != "(") && (stoi(Expression[i]) <= 0 || stoi(Expression[i]) > 0))
        {
            ch = Expression[i];
            OutputStack.push(ch);
        }
        else if (Expression[i] == "(")
        {
            ch = Expression[i];
            Inputstack.push(ch);
        }

        else if (Expression[i] == ")")
        {
            for (int j = i; Inputstack.top() != "("; j--)
            {
                ch = Inputstack.top();
                OutputStack.push(ch);
                Inputstack.pop();

            }
            Inputstack.pop();

        }

    }


    while (!(Inputstack.empty()))

    {
        ch = Inputstack.top();
        OutputStack.push(ch);
        Inputstack.pop();
    }

    while (!(OutputStack.empty()))

    {
        ch = OutputStack.top();
        Inputstack.push(ch);
        OutputStack.pop();

    }


    while (Inputstack.size() != 0)
    {
        int num1, num2, result;
        string op;
        if (Inputstack.top() == "*" || Inputstack.top() == "+" || Inputstack.top() == "-" || Inputstack.top() == "/")
        {
            op = Inputstack.top();
            Inputstack.pop();
            ch = OutputStack.top();
            num1 = stoi(ch);
            OutputStack.pop();
            ch = OutputStack.top();
            num2 = stoi(ch);
            OutputStack.pop();
            if (op == "*")
            {
                result = num2 * num1;
                ch = to_string(result);
                OutputStack.push(ch);
            }
            else if (op == "/")
            {
                result = num2 / num1;
                ch = to_string(result);
                OutputStack.push(ch);
            }
            else if (op == "+")
            {
                result = num2 + num1;
                ch = to_string(result);

                OutputStack.push(ch);
            }
            else if (op == "-")
            {
                result = num2 - num1;
                ch = to_string(result);
                OutputStack.push(ch);
            }


        }
        else
        {
            ch = Inputstack.top();
            OutputStack.push(ch);
            Inputstack.pop();

        }

    }
}


int main(int argc,char* argv[]) 
{
    stack<string> Inputstack,OutputStack;
    std::string Expression[100];
    string ch;
    std::string temp;
    string choice;
    int MS=0;
    int ExpressionSizeCounter=0;
    int check = 0;


    do {

        do { 
            if (argc > 1) 
            {
                
                check = 1;
                
                    for (int i = 1; i < argc; i++)
                    {
                        temp += argv[i];                      // for command line actions, bonus task
                    }
                    if (!(InputValidation(temp)))
                    {
                        cout << "Invalid input" << endl;
                        return 0;
                    }
                
                
            }
                 
            else
            {
                std::cout << "Enter the Expression you want to evaluate (Please Enter In Correct Format)" << endl;
                std::cin >> temp;
            }
        } while (!(InputValidation(temp)));

        MutlidigitsExpressionAdjust(temp, Expression, ExpressionSizeCounter);
        Calculation(Expression, ExpressionSizeCounter, Inputstack, OutputStack);

        ch = OutputStack.top();
        std::cout << "************************************************************************************" << std::endl;

        std::cout << "The Result is = " << ch << endl;

        if (check == 1)
        {
            return 0;            // we dont need to repeat if the program is executed by the command line arugments!
        }


        do {
            do {
                std::cout << "Choose from the following Actions" << endl << "1- MS ( please enter as it is written here)" << endl << "2- MR" << endl << "3- M+" << endl << "4- MC"<<endl<<"5-repeat y/n" << endl;
                std::cin >> choice;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // to ignore extra input
            } while (choice != "MS" && choice != "MR" && choice != "M+" && choice != "MC" && choice != "n" && choice != "N" && choice != "y" && choice != "Y");
            if (choice == "MS")   // bonus task
            {
                MS = stoi(ch);
                cout << " Stored value is now " << MS << endl;;
            }
            else if (choice == "MR")
            {

                cout << "Stored value is  " << MS << endl;
            }
            else if (choice == "M+")
            {
                MS = MS + stoi(ch);
                cout << "New Stored value is now " << MS << endl;;
            }
            else if (choice == "MC")
            {
                MS = 0;
            }
        } while (choice != "n" && choice != "N");
       
        do {
            cout << "Do you want to repeat the whole process? y/n" << endl;
            cin >> choice;
        } while (choice != "n" && choice != "N" && choice != "y" && choice != "Y");

        // resesting the variables after use
        OutputStack.pop();
        ExpressionSizeCounter = 0;
        temp = " ";
        Expression->erase();
       

    } while (choice=="y" || choice=="Y");


    

   
 

}

