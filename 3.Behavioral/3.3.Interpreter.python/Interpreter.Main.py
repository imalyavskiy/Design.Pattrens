
__doc__  = '''
	Система для вычисления и манипулирования булевыми выражениями. Пример из книги 
	Gang of Four - "Design Patterns: Elements of Reusable Object-Oriented Software"
	'''

from abc import ABCMeta, abstractmethod


class Context:
	"""
	Контекст среды исполнения интерпретатора
	"""

	def __init__(self, variables: dict = {}) -> None:
		"""
		Constructor.

		:param variables: словарь соответствий имен переменных их значениям
		"""
		self._variables = variables

	class ContextException(Exception):
		"""
		Исключение, прокидываемое в случае некорректной работы с данным классом
		"""
		pass

	def lookup(self, name: str) -> bool:
		"""
		Получает значение переменной по ее имени

		:param name: имя переменной
		"""
		if name in self._variables:
			return self._variables[name]
		raise self.ContextException('Неизвестная переменная {}'.format(name))

	def assign(self, name: str, value: bool) -> None:
		"""
		Назначает значение переменной по ее имени

		:param name: имя переменной
		:param value: значение переменной
		"""
		self._variables[name] = value


class BooleanExp(metaclass=ABCMeta):
	"""
	Абстрактное логическое выражение
	"""

	@abstractmethod
	def evaluate(self, context: Context) -> bool:
		"""
		Получение результата логического выражения
		"""
		pass


class ConstantExp(BooleanExp):
	"""
	Логическая константа
	"""

	def __init__(self, value: bool):
		"""
		Constructor.

		:param value: значение выражения (True или False)
		"""
		self._value = value

	def evaluate(self, context: Context):
		return self._value


class VariableExp(BooleanExp):
	"""
	Логическая переменная (значение переменных хранится в объекте контекста интерпретатора)
	"""

	def __init__(self, name: str) -> None:
		"""
		Constructor.

		:param name: название переменной
		"""
		self._name = name

	def evaluate(self, context: Context) -> bool:
		return context.lookup(self._name)


class BinaryOperationExp(BooleanExp, metaclass=ABCMeta):
	"""
	Абстрактный класс для бинарных логических операций
	"""

	def __init__(self, left: BooleanExp, right: BooleanExp) -> None:
		"""
		Constructor.

		:param left: левый операнд
		:param right: правый операнд
		"""
		self._left = left
		self._right = right


class AndExp(BinaryOperationExp):
	"""
	Конъюнкция
	"""

	def evaluate(self, context: Context) -> bool:
		return self._left.evaluate(context) and self._right.evaluate(context)


class OrExp(BinaryOperationExp):
	"""
	Дизъюнкция
	"""

	def evaluate(self, context: Context) -> bool:
		return self._left.evaluate(context) or self._right.evaluate(context)


class NotExp(BooleanExp):
	"""
	Отрицание
	"""

	def __init__(self, operand: BooleanExp) -> None:
		"""
		Constructor.

		:param operand: операнд, к которому применяется операция
		"""
		self._operand = operand

	def evaluate(self, context: Context) -> bool:
		return not self._operand.evaluate(context)


def execute_test(context: Context, x: bool, y: bool) -> None:
	"""
	Функция для выполнения тестирования нашего интерпретатора
	"""
	context.assign('x', x)
	context.assign('y', y)
	expression = OrExp(		# (True and x) or (у and (not x))
		AndExp(ConstantExp(True), VariableExp('x')), 
		AndExp(VariableExp('y'), NotExp(VariableExp('x')))
	)
	print(expression.evaluate(context))


if __name__ == '__main__':
	print('OUTPUT:')
	context = Context()
	execute_test(context, True, False)
	execute_test(context, False, True)
	execute_test(context, False, False)

'''
OUTPUT:
True
True
False
'''