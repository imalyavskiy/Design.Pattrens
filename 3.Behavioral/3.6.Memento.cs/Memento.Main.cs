// Пример паттерна Memento(Хранитель)

using System;
using System.Collections.Generic;

namespace DoFactory.GangOfFour.Memento.Behavioral
{
    /// <summary>
    /// Стартовый класс MainApp для демонстрации поведенческого паттерна Memento(Хранитель)
    /// </summary>
    class MainApp
    {
        private delegate void Execute();

        /// <summary>
        /// Массив пар(кортежей) сопряжения имён алгоритмов и методов его исполнения
        /// </summary>
        private Tuple<string, Execute>[] algorithms;

        protected MainApp()
        {
            algorithms = new Tuple<string, Execute>[3] {
                new Tuple<string, Execute>("standard", this.ExecuteStandard),
                new Tuple<string, Execute>("variant" , this.ExecuteVariant),
                new Tuple<string, Execute>("improved", this.ExecuteImproved)
            };
        }

        /// <summary>
        /// Запускает стандартную реализацию паттерна
        /// </summary>
        protected void ExecuteStandard()
        {
            Standard.Originator originator = new Standard.Originator();
            originator.State = "On";

            // Сохраним начальное состояние
            Standard.Caretaker caretaker = new Standard.Caretaker();
            caretaker.Memento = originator.CreateMemento();

            // Поменяет состояние экземпляра класса источника
            originator.State = "Off";

            // Восстановим состояние класса источника
            originator.SetMemento(caretaker.Memento);
        }

        /// <summary>
        /// Запускает вариант реализации паттерна
        /// </summary>
        protected void ExecuteVariant()
        {
            Variant.Originator foo = new Variant.Originator("Test", 15);

            foo.Print();

            Variant.Caretaker ct1 = new Variant.Caretaker();
            Variant.Caretaker ct2 = new Variant.Caretaker();

            ct1.SaveState(foo);
            foo.IntProperty += 152;
            foo.Print();

            ct2.SaveState(foo);

            ct1.RestoreState(foo);
            foo.Print();

            ct2.RestoreState(foo);
            foo.Print();
        }

        /// <summary>
        /// Запускает улучшенную реализацию паттерна
        /// </summary>
        protected void ExecuteImproved()
        {
            Improved.Caretaker caretaker = new Improved.Caretaker();

            Improved.IShape[] shapes = { new Improved.RectOriginator(10, 20, 3, 5), new Improved.CircleOriginator(5, 2, 10) };

            //Выводит:
            // Rectangle 3x5 at (10, 20)
            // Circle with radius 10 at (5, 2)
            Improved.Caretaker.Draw(shapes);

            //Сохраняем состояния фигур
            IEnumerable<Improved.IMemento> states = Improved.Caretaker.SaveStates(shapes);

            //Изменяем положение фигур
            Improved.Caretaker.MoveAndScale(shapes);

            //Выводит:
            // Rectangle 30x50 at (13, 22)
            // Circle with radius 100 at (8, 4)
            Improved.Caretaker.Draw(shapes);

            //Восстановление старого положения фигур
            Improved.Caretaker.RestoreStates(states);

            //Выводит:
            // Rectangle 3x5 at (10, 20)
            // Circle with radius 10 at (5, 2)
            Improved.Caretaker.Draw(shapes);
        }

        /// <summary>
        /// Точка входа консольного приложения.
        /// </summary>
        static void Main(string[] args)
        {
            MainApp app = new MainApp();

            bool executed = false;
            
            ///
            /// проеверяем наличие аргумента
            ///
            if (0 == args.Length)
            {
                Console.WriteLine("Nothing selected.");
                Console.WriteLine("Please set a name of the example:");
                foreach(Tuple<string, Execute> algo in app.algorithms)
                    Console.WriteLine(string.Format("\t{0} - for {0}", algo.Item1));

                return;
            }

            ///
            /// Ищем принятый аргумент, если есть - исполняем сопряжённый метод
            /// 
            foreach (Tuple<string, Execute> algo in app.algorithms)
            {
                if (executed = algo.Item1 == args[0])
                {
                    Console.WriteLine(System.String.Format("Executing the \"{0}\"...", args[0]));
                    algo.Item2();
                    break;
                }
            }

            ///
            /// Если ничего не было исполнено - сообщаем об ошибке
            /// 
            if (!executed)
                Console.WriteLine("Nothing happen because no such executor as passed.");

            ///
            /// Ждём нажатия
            /// 
            System.Console.WriteLine("Press a key to exit.");
            Console.ReadKey();
        }
    }
}