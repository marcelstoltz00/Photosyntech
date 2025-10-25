#include "GetSuggestionCommand.h"
#include "../mediator/Customer.h"
#include "../mediator/SuggestionFloor.h"
#include <stdexcept>

GetSuggestionCommand::GetSuggestionCommand(Customer *customer, SuggestionFloor *suggestionFloor)
	: customer(customer), suggestionFloor(suggestionFloor)
{
	if (customer == nullptr)
	{
		throw std::invalid_argument("GetSuggestionCommand: customer cannot be null");
	}
	if (suggestionFloor == nullptr)
	{
		throw std::invalid_argument("GetSuggestionCommand: suggestionFloor cannot be null");
	}
}

void GetSuggestionCommand::execute()
{
	if (customer == nullptr)
	{
		throw std::runtime_error("GetSuggestionCommand::execute(): customer is null");
	}
	if (suggestionFloor == nullptr)
	{
		throw std::runtime_error("GetSuggestionCommand::execute(): suggestionFloor is null");
	}

	// Route request through suggestion floor mediator
	// The mediator coordinates with available staff to generate recommendations
	suggestionFloor->assist();
}

void GetSuggestionCommand::undo()
{
	// No-op: This is a read-only operation
	// No state changes occur, so undo performs no action
	// The suggestion history remains for display purposes
}
