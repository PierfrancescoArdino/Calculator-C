#include <gtkmm.h>
#include "functions.h"
#include <iostream>

using namespace std;
using namespace Gtk;
class Calculator : public Window
{
    // controls

protected:
    Grid calcGrid;
    Label labelTextToDisplay;
    Entry entryTextToDisplay;
    Button button0;
    vector<vector<Button>> buttonMatrix;
    Button equalButton;
    Button dotButton;
    Button leftParButton;
    Button rightParButton;
    vector<Button> operationButton;
    bool expResult;

    // methods

public: Calculator()
    {
        expResult=false;
        buttonMatrix.resize(3);
        set_border_width(12);
        for(int i=0; i< buttonMatrix.size();i++)
        {
            buttonMatrix[i].resize(3);
        }
        operationButton.resize(5);
        set_border_width(10);

        // vBoxMain
        add(calcGrid);

        // labelTextToDisplay
        labelTextToDisplay.set_label("Expression to compute:");
        calcGrid.attach(labelTextToDisplay,0,0,4,3);
        // entryTextToDisplay
        entryTextToDisplay.set_text("");
        calcGrid.attach(entryTextToDisplay,0,3,4,3);

        /*// buttonDisplay
        buttonDisplay.set_label("Display");
        buttonDisplay.signal_clicked().connect
                (
                        sigc::mem_fun
                                (
                                        *this,
                                        &Calculator::buttonDisplayClicked
                                )
                );
        vBoxMain.add(buttonDisplay);
        buttonDisplay.show();*/
        //button0
        int i=2;
        int j=0;
        int label=1;
        for(vector<Button> &buttonRow : buttonMatrix)
        {
            j=0;
            for(Button &button : buttonRow)
            {

                button.set_label(to_string(label));
                button.signal_clicked().connect(
                        sigc::bind<int>(sigc::mem_fun(*this, &Calculator::numberButtonClicked), label));
                calcGrid.attach(button,j,i+6,1,1);
                label++;
                j++;
            }
            i--;
        }
        button0.set_label("0");
        button0.signal_clicked().connect(
                sigc::bind<int>(sigc::mem_fun(*this, &Calculator::numberButtonClicked), 0));
        calcGrid.attach(button0,0,9,1,1);
        dotButton.set_label(".");
        dotButton.signal_clicked().connect(
                sigc::bind<int>(sigc::mem_fun(*this, &Calculator::numberButtonClicked), 10));
        calcGrid.attach(dotButton,1,9,1,1);
        std::cout<<calcGrid.get_border_width()<<std::endl;
        i = 4;
        for(Button &operation :operationButton)
        {
            string label ="";
            switch(i){
                case 0:
                    label ="+";
                    break;
                case 1:
                    label ="-";
                    break;
                case 2:
                    label ="*";
                    break;
                case 3:
                    label ="/";
                    break;
                case 4:
                    label ="^";
                    break;
            }
            operation.set_label(label);
            operation.signal_clicked().connect(
                    sigc::bind<int>(sigc::mem_fun(*this, &Calculator::operationButtonClicked), i));
            if(label != "^") {
                calcGrid.attach(operation, 3, 9 - i, 1, 1);

            } else{
                calcGrid.attach(operation, 2, 9, 1, 1);
            }
            i--;
        }
        equalButton.set_label("=");
        equalButton.signal_clicked().connect(sigc::mem_fun(*this, &Calculator::equalButtonClicked));
        calcGrid.attach(equalButton,4,8,1,2);
        equalButton.show();
        leftParButton.set_label("(");
        leftParButton.signal_clicked().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &Calculator::parButtonClicked),"("));
        calcGrid.attach(leftParButton,4,6,1,1);
        rightParButton.set_label(")");
        rightParButton.signal_clicked().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &Calculator::parButtonClicked),")"));
        calcGrid.attach(rightParButton,4,7,1,1);
        calcGrid.show_all();


    }

    // event handlers

protected:void numberButtonClicked(int index)
    {
        if(expResult == true){
            entryTextToDisplay.set_text("");
            expResult=false;
        }
        string text = entryTextToDisplay.get_text();
        if(index ==10)
        {
            text.append(".");
        }
        else
        {
        text.append(to_string(index));
        }
        entryTextToDisplay.set_text(text);
    }
protected:void parButtonClicked(string parenthesis)
    {
        if(expResult == true){
            entryTextToDisplay.set_text("");
            expResult=false;
        }
        string text = entryTextToDisplay.get_text();
        text.append(parenthesis);
        entryTextToDisplay.set_text(text);
    }
protected:void operationButtonClicked(int index)
    {
        string label="";
        switch(index){
            case 0:
                label ="+";
                break;
            case 1:
                label ="-";
                break;
            case 2:
                label ="*";
                break;
            case 3:
                label ="/";
                break;
            case 4:
                label ="^";
                break;
        }
        string text = entryTextToDisplay.get_text();
        text.append(label);
        entryTextToDisplay.set_text(text);
    }
protected:void equalButtonClicked()
    {
        std::string expression = entryTextToDisplay.get_text();
        entryTextToDisplay.set_text("");
        std::vector<std::string> postfixExpression;
        postfixExpression = createPostfix(expression);
        std::cout << "Input Expression \n " << expression << std::endl;
        std::cout <<"PostFix expression" << std::endl;
        std::for_each(postfixExpression.begin(), postfixExpression.end(), [](std::string i)->void {std::cout << i << " ";});
        std::cout<<std::endl;
        float result = evaluateExpression(postfixExpression);
        std::cout << "The result is :   \n" << result <<std::endl;
        entryTextToDisplay.set_text(to_string(result));
        expResult = true;

    }
};

int main (int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app =
            Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    Calculator application;
    application.set_default_size(300,200);
    return app->run(application);
}

