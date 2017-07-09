using System;
namespace DoFactory.GangOfFour.Memento.Behavioral.Variant
{
    public interface IOriginator
    {
        object GetMemento();
        void SetMemento(object memento);
    }

    public class Originator
        : IOriginator
    {
        public string StringProperty
        {
            get;
            private set;
        }

        public int IntProperty
        {
            get;
            set;
        }

        public Originator(string stringPropertyValue, int intPropertyValue = 0)
        {
            StringProperty = stringPropertyValue;
            IntProperty = intPropertyValue;
        }

        public void Print()
        {
            Console.WriteLine("=============");
            Console.WriteLine("StringProperty value: {0}", StringProperty);
            Console.WriteLine("IntProperty value: {0}", IntProperty);
            Console.WriteLine("=============");
        }

        object IOriginator.GetMemento()
        {
            return new Memento { StringProperty = this.StringProperty, IntProperty = this.IntProperty };

        }

        void IOriginator.SetMemento(object memento)
        {
            if (Object.ReferenceEquals(memento, null))
                throw new ArgumentNullException("memento");
            if (!(memento is Memento))
                throw new ArgumentException("memento");
            StringProperty = ((Memento)memento).StringProperty;
            IntProperty = ((Memento)memento).IntProperty;
        }

        class Memento
        {
            public string StringProperty
            {
                get;
                set;
            }

            public int IntProperty
            {
                get;
                set;
            }
        }
    }

    public class Caretaker
    {
        private object m_memento;
        public void SaveState(IOriginator originator)
        {
            if (originator == null)
                throw new ArgumentNullException("originator");
            m_memento = originator.GetMemento();
        }

        public void RestoreState(IOriginator originator)
        {
            if (originator == null)
                throw new ArgumentNullException("originator");
            if (m_memento == null)
                throw new InvalidOperationException("m_memento == null");
            originator.SetMemento(m_memento);
        }
    }
}