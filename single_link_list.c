#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK     0
#define ERROR -1
#define TRUE   0
#define FALSE -1

#define MAXSIZE 20

typedef int status;
typedef int element_type;

typedef struct node{
	element_type data;
	struct node *next;
}node, *link_list;

void error(char *str)
{
	perror(str);
}

status list_init(link_list *l)
{
	(*l) = (link_list)malloc(sizeof(struct node));
	if(!(*l))
		error("Out of memory in initiating the list.\n");
	(*l)->next = NULL;
	return OK;
}

int list_length(link_list l)
{
	int i = 0;
	link_list p = l->next;
	while(p){
		++i;
		p = p->next;
	}
	return i;
}

status list_clear(link_list *l)
{
	link_list p, q = (*l)->next;
	while(q){
		p = q->next;
		free(q);
		q = p;
	}
	(*l)->next = NULL;
	return OK;
}

status list_visit(element_type c)
{
	printf("-> %d",c);
	return OK;
}

status list_traverse(link_list l)
{
	link_list p = l->next;
	while(p){
		list_visit(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

status list_traverse_limit(link_list l, int n)
{
	link_list p = l->next;
	int i = 0;
	while(p && i < n){
		list_visit(p->data);
		p = p->next;
		++i;
	}
	return OK;
}

status get_element(link_list l, int i, element_type *e)
{
	link_list p = l->next;
	int j = 1;
	while(p && j < i){
		p = p->next;
		j++;
	}
	if(!p || j > i)
		error("Can not find the element, please check.\n");
	*e = p->data;
		return OK;
}                                      

int locate_element(link_list l , element_type e)
{
	int i = 0;
	link_list p = l->next;
	while(p){
		if(p->data == e)
			return i;
		p = p->next;
		i++;
	}
	return -1;
}

void list_create_tail(link_list *l, int n)
{
	link_list p, r;
	int i;
	srand(time(0));
	(*l) = (link_list)malloc(sizeof(struct node));
	r = *l;
	for(i = 0; i < n; i++){
		p = (link_list)malloc(sizeof(struct node));
		p->data = rand()%100 + 1;
		p->next = NULL;
		r->next = p;
		r = p;
	}
	r->next = NULL;
} 

void list_create_head(link_list *l, int n)
{
	int i;
	link_list p;
	srand(time(0));
	(*l) = (link_list)malloc(sizeof(struct node));
	for(i = 0; i < n; i++){
		p = (link_list)malloc(sizeof(struct node));
		p->data = rand()%100 + 1;
		p->next = (*l)->next;
		(*l)->next = p;
	}	
}

// derek's version
status list_insertd(link_list *l, int i, element_type e)
{
	int j;
	link_list pre, pnext, p;
	if(i < 0 || i >= list_length(*l))
		error("Insert the wrong lacation.\n");
	pre = *l;
	pnext = (*l)->next;
	for(j = 0, pre = pnext; j < i; j++, pnext = pnext->next);
	p = (link_list)malloc(sizeof(struct node));
	p->data = e;
	p->next = pnext;
	pre->next = p;
	return OK;	
}

status list_insert(link_list *l, int i, element_type e)
{
	int j = 1;
	link_list p,s;
	p = *l;
	while(p && j < i){
		p = p->next;
		j++;	
	}
	if(!p || j > i)
		error("Insert the wrong location.\n");
	s = (link_list)malloc(sizeof(struct node));
	s->data = e;	
	s->next = p->next;
	p->next = s;
	return OK;
}

status list_delete(link_list *l, int i, element_type *e)
{
	link_list p,s;
	int j = 1;
	p = *l;
	while(p && j < i){
		p = p->next;
		j++;
	}
	if(!p || j > i)
		error("Deleting the wrong location.\n");
	s = p->next;			// the ith element
	*e = s->data;
	p->next = s->next;
	free(s);
	return OK;
}

link_list list_reverse1(link_list l)
{
	link_list pre, pnxt, ptmp;
	if(!l || !(l->next))
		return l;
	pre = l->next;
	pnxt = pre->next;
	pre->next = NULL;
	while(pnxt){
		ptmp = pnxt->next;
		pnxt->next = pre;
		pre = pnxt;
		pnxt = ptmp;
	}
	l->next = pre;
	return l;
}

link_list list_reverse2(link_list l)
{
	link_list current, p;
	if(!l || !(l->next))
		return l;
	current = l->next;
	while(current->next){
		p = current->next;
		current->next = p->next;
		p->next = l->next;
		l->next = p;
	}
	return l;
}

//Derek's version
link_list list_reverse3d(link_list l)
{
	link_list new_list, new_node, p, ptmp;
	if(!l || !(l->next))
		return l;
	new_list = (link_list)malloc(sizeof(struct node));
	new_list->next = NULL;
	p = l->next;
	while(p){
		ptmp = p;
		new_node = (link_list)malloc(sizeof(struct node));
		new_node->data = p->data;
		new_node->next = new_list->next;
		new_list->next = new_node;
		p = ptmp->next;
		free(ptmp);
	}
	l = new_list;
	free(new_list);
	return l;
}

link_list list_reverse3(link_list l)
{
	link_list new_list;
	link_list tmp;
	if(l == NULL || !(new_list = (link_list)malloc(sizeof(struct node))))
		error("Reverse error.\n");
	new_list->data = l->data;
	new_list->next = NULL;
	while(l->next){
		tmp = new_list->next;
		new_list->next = l->next;
		l->next = l->next->next;
		new_list->next->next = tmp;
	}
	free(l);
	return new_list;
}

status get_nth_node_from_back(link_list l, int n, element_type *e)
{
	link_list pre, pnxt;
	int i = 1;
	if(!l || !(l->next))
		return ERROR;
	pnxt = pre = l->next;
	while(i < n && pnxt){
		pnxt = pnxt->next;
		i++;
	}
	if(i < n && !pnxt)
		error("Getting element out of range.\n");
	while(pnxt->next){
		pnxt = pnxt->next;
		pre = pre->next;
	}
	*e = pre->data;
	return OK;
}

status get_mid_node(link_list l, element_type *e)
{
	link_list pre, pnxt;
	if(!l || !(l->next))
		return ERROR;
	pnxt = pre = l->next;
	while(pnxt->next){
		if(pnxt->next->next){
			pre = pre->next;
			pnxt = pnxt->next->next;
		}else
			pnxt = pnxt->next;
	}
	*e = pre->data;
	return OK;
}


int has_loop(link_list l)
{
	link_list p_slow, p_fast;
	if(!l || !(l->next))
		return ERROR;
	p_slow = p_fast = l->next;
	while(p_fast->next){
		if(p_fast->next->next){
			p_fast = p_fast->next->next;
			p_slow = p_slow->next;
			if(p_fast == p_slow)
				return TRUE;
		}else
			break;
	}
	return FALSE;
}

status build_list_loop(link_list *l, int num)
{
	int j = 0;
	link_list p_looped, p_end;
	p_looped = p_end = *l;
	if(num < 0 || !(*l) || num >= list_length(*l))
		error("Building loop link list error.\n");
	while(p_end->next){
		if(j < num){
			j++;
			p_looped = p_looped->next;
		}
		p_end = p_end->next;	
	}
	p_end->next = p_looped;
	return OK; 
}

void remove_dual_node(link_list *l)
{
	link_list p_cur, p_nxt, p_tmp;
	p_cur = (*l)->next;
	if(!(*l) || !(*l)->next)
		error("Removing link list error.\n");
	while(p_cur){
		p_nxt = p_cur;
		while(p_nxt->next){
			if(p_nxt->next->data == p_cur->data){
				p_tmp = p_nxt->next;
				p_nxt->next = p_nxt->next->next;
				free(p_tmp);
			}else 			
				p_nxt = p_nxt->next;			
		}
		p_cur = p_cur->next;
	}			
}

int main(char *argv, int argc)
{
	link_list l;
	status i;
	int j,k,pos,value;
	int opp;
	element_type e;

	i = list_init(&l);
	printf("The link list is already initiated, list_length(l) = %d.\n",list_length(l));

	printf("\n01. Creating the list from head. \n02. Creating the list from tail. \n03. Traverse the list. \n04. Insert.");
	printf("\n05. Delete. \n06. Access node data. \n07. Search some nodes. \n08. Clear the list");
	printf("\n09. Reverse the list. \n10. Find the Nth node from back. \n11. Find the middle node of the list. \n12. If the list has loop.");
	printf("\n13. Buid loop. \n14. Delete dual node in the loop. \n00. Quit. \nEnter your choice:\n");

	while(opp != '0'){
		scanf("%d",&opp);
		switch(opp){
		case 1:
			list_create_head(&l, 10);
			printf("Creating the list from head.\n");
			list_traverse(l);
			printf("\n");
			break;
		case 2:
			list_create_tail(&l, 10);
			printf("Creating the list from tail.\n");
			list_traverse(l);
			printf("\n");
			break;
		case 3:
			list_traverse(l);
			printf("\n");
			break;
		case 4:
			printf("Where do you want to insert?\n");
			scanf("%d",&pos);
			printf("What is the value?\n");
			scanf("%d", &value);
			list_insert(&l, pos, value);
			list_traverse(l);
			printf("\n");
			break;
		case 5:
			printf("Which elemenet do you want to delete?\n");
			scanf("%d",&pos);
			list_delete(&l, pos, &e);
			printf("Delete the %dth element %d successful, the current list is:\n", pos, e);
			list_traverse(l);
			printf("\n");
			break;
		case 6:
			printf("Which element do you want to get?\n");
			scanf("%d",&pos);
			get_element(l, pos, &e);
			printf("The %dth element is:%d.\n", pos , e);
			printf("\n");
			break;
		case 7:
			printf("Element you want to search:\n");
			scanf("%d",&pos);
			k = locate_element(l, pos);
			if(k)
				printf("The %dth element is:%d\n",k, pos);
			else
				printf("Value %d is not existed.\n", pos);
			printf("\n");
			break;
		case 8:
			i = list_clear(&l);
			printf("After clearing: list_length(l) = %d\n", list_length(l));
			list_traverse(l);
			printf("\n");
			break;
		case 9:
			// l = list_reverse2(l);
			// list_reverse2(l);
			list_reverse1(l);
			// l = list_reverse3(l);
			// l = list_reverse3d(l);
			printf("After reserve:\n");
			list_traverse(l);
			printf("\n");
			break;
		case 10:
			printf("Which node would you want to find from back?\n");
			scanf("%d",&value);
			get_nth_node_from_back(l, value, &e);
			printf("The %dth node down is %d.\n", value, e);
			printf("\n");
			break;
		case 11:
			get_mid_node(l, &e);
			printf("The middle node of the list is:%d.\n", e);
			printf("\n");
			break;
		case 12:
			if(has_loop(l) == TRUE)
				printf("The list has loop.\n");
			else 
				printf("The list has no loop.\n");
			printf("\n");
			break;	
		case 13:
			printf("Where do you want to start building the loop?\n");
			scanf("%d", &pos);
			build_list_loop(&l, pos);
			list_traverse_limit(l, 20);
			printf("\n");
			break;	
		case 14:
			remove_dual_node(&l);
			list_traverse(l);
			printf("\n");
			break;
		case 0:
			exit(0);
		}
	}

}






















































































































































































































































































































































































































                                                                          
