using System;

namespace Digital_Patterns.Behavioral.State
{
    public interface IAutomataState
    {
        String         GotApplication();
        String         CheckApplication();
        String         RentApartment();
        String         DispenseKeys();
    }

    public interface IAutomata
    {
        void           GotApplication();
        void           CheckApplication();
        void           RentApartment();

        void           SetState(IAutomataState s);

        IAutomataState GetWaitingState();
        IAutomataState GetGotApplicationState();
        IAutomataState GetApartmentRentedState();
        IAutomataState GetFullyRentedState();

        Int32 Count { get; set; }
    }

    public class Automata : IAutomata
    {
        private IAutomataState _waitingState;
        private IAutomataState _gotApplicationState;
        private IAutomataState _apartmentRentedState;
        private IAutomataState _fullyRentedState;
        private IAutomataState _state;
        private Int32          _count;

        public Automata(Int32 n)
        {
            _count = n;
            _waitingState           = new WaitingState(this);
            _gotApplicationState    = new GotApplicationState(this);
            _apartmentRentedState   = new ApartmentRentedState(this);
            _fullyRentedState       = new FullyRentedState(this);
            _state = _waitingState;
        }

        public void GotApplication()
        {
            Console.WriteLine(_state.GotApplication());
        }

        public void CheckApplication()
        {
            Console.WriteLine(_state.CheckApplication());
        }

        public void RentApartment()
        {
            Console.WriteLine(_state.RentApartment());
            Console.WriteLine(_state.DispenseKeys());
        }

        public void SetState(IAutomataState s) { _state = s; }

        public IAutomataState GetWaitingState() { return _waitingState; }

        public IAutomataState GetGotApplicationState() { return _gotApplicationState; }

        public IAutomataState GetApartmentRentedState() { return _apartmentRentedState; }

        public IAutomataState GetFullyRentedState() { return _fullyRentedState; }

        public int Count
        {
            get { return _count; }
            set { _count = value; }
        }
    }

    public class WaitingState : IAutomataState
    {
        private const String _response = "You have to submit an application.";

        private Automata _automata;

        public WaitingState(Automata automata)
        {
            _automata = automata;
        }

        public String GotApplication()
        {
            _automata.SetState(_automata.GetGotApplicationState());
            return "Thanks for the application.";
        }

        public String CheckApplication() { return _response; }

        public String RentApartment()    { return _response; }

        public String DispenseKeys()     { return _response; }
    }

    public class GotApplicationState : IAutomataState
    {
        private const String _response = "You must have your application checked.";
        
        private Automata _automat;
        private readonly Random _random;

        public GotApplicationState(Automata automat)
        {
            _automat = automat;
            _random = new Random(System.DateTime.Now.Millisecond);
        }

        public String GotApplication() { return "We already got your application."; }

        public String CheckApplication()
        {
            var yesNo = _random.Next() % 10;

            if (yesNo > 4 && _automat.Count > 0)
            {
                _automat.SetState(_automat.GetApartmentRentedState());
                return "Congratulations, you were approved.";
            }
            else
            {
                _automat.SetState(_automat.GetWaitingState());
                return "Sorry, you were not approved.";
            }
        }

        public String RentApartment() { return _response; }

        public String DispenseKeys() { return _response; }
    }

    public class ApartmentRentedState : IAutomataState
    {
        private const String _response = "Hang on, we'ra renting you an apartmeny.";

        private Automata _automat;

        public ApartmentRentedState(Automata automat)
        {
            _automat = automat;
        }

        public String GotApplication() { return _response; }

        public String CheckApplication() { return _response; }

        public String RentApartment()
        {
            _automat.Count = _automat.Count - 1;
            return "Renting you an apartment....";
        }

        public String DispenseKeys()
        {
            if (_automat.Count <= 0)
                _automat.SetState(_automat.GetFullyRentedState());
            else
                _automat.SetState(_automat.GetWaitingState());
            return "Here are your keys!";
        }
    }

    public class FullyRentedState : IAutomataState
    {
        private const String _response = "Sorry, we're fully rented.";

        private Automata _automat;

        public FullyRentedState(Automata automat)
        {
            _automat = automat;
        }

        public String GotApplication()      { return _response; }

        public String CheckApplication()    { return _response; }

        public String RentApartment()       { return _response; }

        public String DispenseKeys()        { return _response; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var automata = new Automata(9);

            automata.GotApplication();
            automata.CheckApplication();
            automata.RentApartment();
        }
    }
}