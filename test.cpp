void LinkedList<Type>::RemoveAllof(Type data) {//removeAllof method, find all the data same as passed in data and remove them
  Node<Type>* temp2 = new Node<Type>();//create a new temp value
  temp2 = Head;//start from head
	
	if (Head->Data.getColor() == data.getColor()) {
	  Head = Head->next;//if head is the one we are looking for remove it
	  length--;
	}
	while (temp2->next != NULL) {//keep moving to the end of linked list
	  if (temp2->next->Data.getColor() == data.getColor()) {//if find data same as passed in data
	    temp2->next = temp2->next->next;//change the pointer point to the next next data. which will remove the data we want to remove
			length--;
		}
		else {
		  temp2 = temp2->next;//if not same color keep moving
		}
	}
} 