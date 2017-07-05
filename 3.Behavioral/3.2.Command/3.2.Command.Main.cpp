#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Document
{
	std::vector<std::string> data;
public:
	typedef std::shared_ptr<Document> ptr;

	void Insert(uint32_t line, const std::string & str)
	{
		if (line <= data.size())
			data.insert(data.begin() + line, str);
		else
			std::cout << "Error!" << std::endl;
	}

	void Remove(uint32_t line)
	{
		if (!(line > data.size()))
			data.erase(data.begin() + line);
		else
			std::cout << "Error!" << std::endl;
	}

	std::string& operator [] (int x)
	{
		return data[x];
	}

	void Show()
	{
		for (uint32_t i = 0; i < data.size(); ++i)
			std::cout << i + 1 << ". " << data[i] << std::endl;
	}
};

class Command
{
protected:
	Document::ptr doc;

public:
	typedef std::shared_ptr<Command> ptr;

	virtual void Execute() = 0;
	virtual void unExecute() = 0;

	void setDocument(Document::ptr& _doc)
	{
		doc = _doc;
	}
};

class InsertCommand : public Command
{
	int line;
	std::string str;
public:
	InsertCommand(int _line, const std::string & _str) : line(_line), str(_str) {}

	void Execute() override
	{
		doc->Insert(line, str);
	}

	void unExecute() override
	{
		doc->Remove(line);
	}
};

class Receiver
{
private:
	std::vector<Command::ptr> DoneCommands;
	Document::ptr doc;
	Command::ptr command;

public:
	Receiver()
		: doc(std::make_shared<Document>())
	{

	}

	void Insert(int line, std::string str)
	{
		command.reset(new InsertCommand(line, str));
		command->setDocument(doc);
		command->Execute();
		DoneCommands.push_back(command);
	}

	void Undo()
	{
		if (DoneCommands.size() == 0)
		{
			std::cout << "There is nothing to undo!" << std::endl;
		}
		else
		{
			command = DoneCommands.back();
			DoneCommands.pop_back();
			command->unExecute();
			
			// Don't forget to delete command!!!
			command.reset();
		}
	}

	void Show()
	{
		doc->Show();
	}
};

int main()
{
	int line_no = 0;
	std::string str;
	Receiver receiver;
	
	auto print_doc = [&receiver]()
	{
		std::cout << "$$$DOCUMENT$$$" << std::endl;
		receiver.Show();
		std::cout << "$$$DOCUMENT$$$" << std::endl;
	};

	while (str != "e")
	{
		std::cout << "What to do: \n1.Add a line\n2.Undo last command" << std::endl;
		std::getline(std::cin, str);
		if(str == "1")
		{
			std::cout << "What line to insert: ";
			std::getline(std::cin, str);
			line_no = std::atoi(str.c_str());
			--line_no;

			std::cout << "What to insert: ";
			std::getline(std::cin, str);

			receiver.Insert(line_no, str);

			print_doc();
		}
		else if(str == "2")
		{
			receiver.Undo();

			print_doc();
		}
		else		
		{
			std::cout << str << " - pressed. Please press 1 or 2" << std::endl;
		}
	}
}