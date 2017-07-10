using System;
using System.Collections.Generic;

namespace DoFactory.GangOfFour.Memento.Behavioral.Improved
{
    public interface IOriginator
    {
        IMemento GetState();
    }

    public interface IShape : IOriginator
    {
        void Draw();
        void Scale(double scale);
        void Move(double dx, double dy);
    }

    public interface IMemento
    {
        void RestoreState();
    }

    public class CircleOriginator : IShape
    {
        private class CircleMemento : IMemento
        {
            private readonly double x;
            private readonly double y;
            private readonly double r;
            private readonly CircleOriginator originator;

            public CircleMemento(CircleOriginator originator)
            {
                this.originator = originator;
                x = originator.x;
                y = originator.y;
                r = originator.r;
            }

            public void RestoreState()
            {
                originator.x = x;
                originator.y = y;
                originator.r = r;
            }
        }

        double x;
        double y;
        double r;

        public CircleOriginator(double x, double y, double r)
        {
            this.x = x;
            this.y = y;
            this.r = r;
        }

        public void Draw()
        {
            Console.WriteLine("Circle with radius {0} at ({1}, {2})", r, x, y);
        }

        public void Scale(double scale)
        {
            r *= scale;
        }

        public void Move(double dx, double dy)
        {
            x += dx;
            y += dy;
        }

        public IMemento GetState()
        {
            return new CircleMemento(this);
        }
    }

    public class RectOriginator : IShape
    {
        private class RectMemento : IMemento
        {
            private readonly double x;
            private readonly double y;
            private readonly double w;
            private readonly double h;
            private readonly RectOriginator originator;

            public RectMemento(RectOriginator originator)
            {
                this.originator = originator;
                x = originator.x;
                y = originator.y;
                w = originator.w;
                h = originator.h;
            }

            public void RestoreState()
            {
                originator.x = x;
                originator.y = y;
                originator.w = w;
                originator.h = h;
            }
        }

        double x;
        double y;
        double w;
        double h;

        public RectOriginator(double x, double y, double w, double h)
        {
            this.x = x;
            this.y = y;
            this.w = w;
            this.h = h;
        }

        public void Draw()
        {
            Console.WriteLine("Rectangle {0}x{1} at ({2}, {3})", w, h, x, y);
        }

        public void Scale(double scale)
        {
            w *= scale;
            h *= scale;
        }

        public void Move(double dx, double dy)
        {
            x += dx;
            y += dy;
        }

        public IMemento GetState()
        {
            return new RectMemento(this);
        }
    }

    public class Caretaker
    {
        public static void Draw(IEnumerable<IShape> shapes)
        {
            foreach (IShape shape in shapes)
            {
                shape.Draw();
            }
        }

        public static void MoveAndScale(IEnumerable<IShape> shapes)
        {
            foreach (IShape shape in shapes)
            {
                shape.Scale(10);
                shape.Move(3, 2);
            }
        }

        public static IEnumerable<IMemento> SaveStates(IEnumerable<IShape> shapes)
        {
            LinkedList<IMemento> states = new LinkedList<IMemento>();
            foreach (IShape shape in shapes)
            {
                states.AddLast(shape.GetState());
            }
            return states;
        }

        public static void RestoreStates(IEnumerable<IMemento> states)
        {
            foreach (IMemento state in states)
            {
                state.RestoreState();
            }
        }
    }
}