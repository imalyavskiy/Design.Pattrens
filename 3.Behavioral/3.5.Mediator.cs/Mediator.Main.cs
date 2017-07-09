// Mediator pattern — Structural example
using System;

namespace DoFactory.GangOfFour.Mediator.Structural
{
    /// <summary>
    /// MainApp startup class for Structural
    /// Mediator Design Pattern.
    /// </summary>
    class MainApp
    {
        /// <summary>
        /// Entry point into console application.
        /// </summary>
        static void Main()
        {
            ConcreteMediator mediator = new ConcreteMediator();

            ConcreteColleague1 collegue_1 = new ConcreteColleague1(mediator);
            ConcreteColleague2 collegue_2 = new ConcreteColleague2(mediator);

            mediator.collegue_1 = collegue_1;
            mediator.collegue_2 = collegue_2;

            collegue_1.Send("How are you?");
            collegue_2.Send("Fine, thanks");

            // Wait for user
            Console.ReadKey();
        }
    }

    /// <summary>
    /// The 'Mediator' abstract class
    /// </summary>
    abstract class Mediator
    {
        public abstract void Send(string message, Colleague colleague);
    }

    /// <summary>
    /// The 'ConcreteMediator' class
    /// </summary>
    class ConcreteMediator : Mediator
    {
        public ConcreteColleague1 collegue_1 { private get; set; }

        public ConcreteColleague2 collegue_2 { private get; set; }

        public override void Send(string message, Colleague colleague)
        {
            if (colleague == collegue_1)
            {
                collegue_2.Notify(message);
            }
            else
            {
                collegue_1.Notify(message);
            }
        }
    }

    /// <summary>
    /// The 'Colleague' abstract class
    /// </summary>
    abstract class Colleague
    {
        protected Mediator mediator;

        // Constructor
        public Colleague(Mediator mediator)
        {
            this.mediator = mediator;
        }
    }

    /// <summary>
    /// A 'ConcreteColleague' class
    /// </summary>
    class ConcreteColleague1 : Colleague
    {
        // Constructor
        public ConcreteColleague1(Mediator mediator)
          : base(mediator)
        {
        }

        public void Send(string message)
        {
            mediator.Send(message, this);
        }

        public void Notify(string message)
        {
            Console.WriteLine("Colleague1 gets message: " + message);
        }
    }

    /// <summary>
    /// A 'ConcreteColleague' class
    /// </summary>
    class ConcreteColleague2 : Colleague
    {
        // Constructor
        public ConcreteColleague2(Mediator mediator)
          : base(mediator)
        {
        }

        public void Send(string message)
        {
            mediator.Send(message, this);
        }

        public void Notify(string message)
        {
            Console.WriteLine("Colleague2 gets message: " + message);
        }
    }
}
/**
* Output
* Colleague2 gets message: How are you?
* Colleague1 gets message: Fine, thanks
*/