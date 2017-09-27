#include <gtkmm.h>
#include "functions.h"
#include <iostream>

using namespace std;
using namespace Gtk;
class Calculator : public Window {
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
    Button sqrtButton;
    Button expButton;
    Button logButton;
    Button squaredButton;
    Button ansButton;
    vector<Button> operationButton;
    bool expResult;
    bool floatNumber;



    // methods
private:
    bool on_key_press_event(GdkEventKey *event) override;
    void numberButtonClicked(int index);
    void operationButtonClicked(string operation);
    void parButtonClicked(string parenthesis);
    void equalButtonClicked();
    void ansButtonClicked();


public:
    Calculator();
};
Calculator::Calculator(){
        expResult=false;
        floatNumber=false;
        buttonMatrix.resize(3);
        add_events(Gdk::KEY_PRESS_MASK);
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
        labelTextToDisplay.set_justify(Gtk::JUSTIFY_CENTER);
        calcGrid.attach(labelTextToDisplay,0,0,6,3);
        // entryTextToDisplay
        entryTextToDisplay.set_text("");
        entryTextToDisplay.set_alignment(Gtk::ALIGN_END);
        calcGrid.attach(entryTextToDisplay,0,3,5,3);
        ansButton.set_label("ans");
        ansButton.signal_clicked().connect(sigc::mem_fun(*this, &Calculator::ansButtonClicked));
        calcGrid.attach(ansButton,5,3,1,3);

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
                    sigc::bind<string>(sigc::mem_fun(*this, &Calculator::operationButtonClicked), label));
            if(label != "^") {
                calcGrid.attach(operation, 3, 9 - i, 1, 1);

            } else{
                calcGrid.attach(operation, 2, 9, 1, 1);
            }
            i--;
        }
        equalButton.set_label("=");
        equalButton.signal_clicked().connect(sigc::mem_fun(*this, &Calculator::equalButtonClicked));
        calcGrid.attach(equalButton,4,9,2,1);
        equalButton.show();
        leftParButton.set_label("(");
        leftParButton.signal_clicked().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &Calculator::parButtonClicked),"("));
        calcGrid.attach(leftParButton,4,6,1,1);
        rightParButton.set_label(")");
        rightParButton.signal_clicked().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &Calculator::parButtonClicked),")"));
        calcGrid.attach(rightParButton,5,6,1,1);
        sqrtButton.set_label("√");
        sqrtButton.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Calculator::operationButtonClicked), "sqrt("));
        calcGrid.attach(sqrtButton,4,7,1,1);
        expButton.set_label("exp");
        expButton.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Calculator::operationButtonClicked), "exp("));
        calcGrid.attach(expButton,5,7,1,1);
        logButton.set_label("log");
        logButton.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Calculator::operationButtonClicked), "log("));
        calcGrid.attach(logButton,4,8,1,1);
        squaredButton.set_label("x^2");
        squaredButton.signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Calculator::operationButtonClicked), "^2"));
        calcGrid.attach(squaredButton,5,8,1,1);
        for(Widget *obj : calcGrid.get_children())
        {
            obj->set_hexpand(true);
            obj->set_vexpand(true);
        }
        calcGrid.set_row_spacing(10);
        calcGrid.set_column_spacing(10);
        calcGrid.set_margin_left(30);
        calcGrid.set_margin_bottom(30);
        calcGrid.set_margin_right(30);
        calcGrid.set_margin_top(30);
        calcGrid.show_all();
    }
    // event handlers

void Calculator::numberButtonClicked(int index)
    {
        if(expResult == true){
            entryTextToDisplay.set_text("");
            entryTextToDisplay.set_position(0);
            expResult=false;
            floatNumber=false;
        }
        string text = entryTextToDisplay.get_text();
        if(index == 10 )
        {
            if(!floatNumber) {
                text.append(".");
                floatNumber = true;
            }

        }
        else
        {
        text.append(to_string(index));
        }
        entryTextToDisplay.set_text(text);
        entryTextToDisplay.set_position(text.size());
    }
void Calculator::parButtonClicked(string parenthesis)
    {
        if(expResult == true){
            entryTextToDisplay.set_text("");
            expResult=false;
            floatNumber=false;
        }
        string text = entryTextToDisplay.get_text();
        text.append(parenthesis);
        entryTextToDisplay.set_text(text);
    }
void Calculator::ansButtonClicked()
{
    if(expResult == true){
        entryTextToDisplay.set_text(entryTextToDisplay.get_text());
        expResult=false;
        floatNumber=false;
    }
}
void Calculator::operationButtonClicked(string operation)
    {
        if(expResult == true){
            entryTextToDisplay.set_text("");
            expResult=false;
            floatNumber=false;
        }
        string text = entryTextToDisplay.get_text();
        text.append(operation);
        entryTextToDisplay.set_text(text);
    }
void Calculator::equalButtonClicked()
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
        entryTextToDisplay.set_position(to_string(result).size());
        expResult = true;

    }
bool Calculator::on_key_press_event(GdkEventKey* key_event)
    {
        string command;
        if((key_event->keyval == GDK_KEY_parenleft) &&
           (key_event->state &(GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_SHIFT_MASK)
        {
            command= "(";
        }else if((key_event->keyval == GDK_KEY_parenright) &&
                 (key_event->state &(GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_SHIFT_MASK)
        {
            command= ")";
        }
        else if(key_event->keyval == GDK_KEY_KP_0 || key_event->keyval == GDK_KEY_0)
        {
            command= "0";
        }
        else if(key_event->keyval == GDK_KEY_KP_1 || key_event->keyval == GDK_KEY_1)
        {
            command= "1";
        }
        else if(key_event->keyval == GDK_KEY_KP_2 || key_event->keyval == GDK_KEY_2)
        {
            command= "2";
        }
        else if(key_event->keyval == GDK_KEY_KP_3 || key_event->keyval == GDK_KEY_3)
        {
            command= "3";
        }
        else if(key_event->keyval == GDK_KEY_KP_4 || key_event->keyval == GDK_KEY_4)
        {
            command= "4";
        }
        else if(key_event->keyval == GDK_KEY_KP_5 || key_event->keyval == GDK_KEY_5)
        {
            command= "5";
        }
        else if(key_event->keyval == GDK_KEY_KP_6 || key_event->keyval == GDK_KEY_6)
        {
            command= "6";
        }
        else if(key_event->keyval == GDK_KEY_KP_7 || key_event->keyval == GDK_KEY_7)
        {
            command= "7";
        }
        else if(key_event->keyval == GDK_KEY_KP_8 || key_event->keyval == GDK_KEY_8)
        {
            command= "8";
        }
        else if(key_event->keyval == GDK_KEY_KP_9 || key_event->keyval == GDK_KEY_9)
        {
            command= "9";
        }
        else if(key_event->keyval == GDK_KEY_plus || key_event->keyval == GDK_KEY_KP_Add){
            command="+";
        }
        else if(key_event->keyval == GDK_KEY_minus || key_event->keyval == GDK_KEY_KP_Subtract){
            command="-";
        }
        else if(key_event->keyval == GDK_KEY_KP_Multiply){
            command="*";
        }
        else if(key_event->keyval == GDK_KEY_KP_Divide){
            command="/";
        }
        else if(key_event->keyval == GDK_KEY_KP_Decimal){
            if(!floatNumber)
            {
                command=".";
                floatNumber=true;
            }
        }
        else if((key_event->keyval == GDK_KEY_asciicircum) &&
                  (key_event->state &(GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_SHIFT_MASK)
        {
            command= "^";
        }
        else if(key_event->keyval == GDK_KEY_KP_Enter || key_event->keyval == GDK_KEY_Return)
        {
            equalButton.activate();
        }
        else if(key_event->keyval == GDK_KEY_BackSpace)
        {
            if(expResult !=true){
                string tmp = entryTextToDisplay.get_text();
                if (tmp != "")
                {
                    tmp.resize(tmp.size()-1);
                    entryTextToDisplay.set_text(tmp);
                    entryTextToDisplay.set_position(tmp.size());
                }
            }
            else
            {
                entryTextToDisplay.set_text("");
                entryTextToDisplay.set_position(0);
                expResult=false;
                floatNumber=false;
            }
        }
        if(command!="")
        {
            if(expResult == true){
                entryTextToDisplay.set_text("");
                expResult=false;
                floatNumber= false;
            }
            string text = entryTextToDisplay.get_text();
            text.append(command);
            entryTextToDisplay.set_text(text);
            entryTextToDisplay.set_position(text.size());

        }
        std::cout<<"Key pressed " << key_event->keyval << std::endl;
        return true;
    }

int main (int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app =
            Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    Calculator application;
    application.set_default_size(600,400);
    application.set_hexpand(true);
    application.set_vexpand(true);
    return app->run(application);
}

