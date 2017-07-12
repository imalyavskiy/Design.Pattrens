'''The ".pyw" extension supresses the console window'''
import imp

if __name__ == '__main__':
    with open('Model.View.Controller.Main.py','rb') as fp:
        Model_View_Controller_Main = imp.load_module( 'Model_View_Controller_Main', fp, 'Model.View.Controller.Main.py', ('.py', 'rb', imp.PY_SOURCE) )
    Model_View_Controller_Main.Run()	