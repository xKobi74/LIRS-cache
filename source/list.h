#ifndef __LIST_H__
#define __LIST_H__

struct list list;

void new_in_list(int name, void *location_in_cash, struct list list, struct element_hash **hash);
struct dlinked_list_element *create_elem(int name, void *location_in_cache);
void delete_element(struct dlinked_list_element **det_elem, struct element_hash **hash);

struct element add_in_list(int name, struct list list, struct element_hash **hash); //return struct delete element
//Добавление пришедшего элемента сверху, удаление нижнего, возвращение копии удаленной структуры

struct element move_up_list(int name, struct list list, struct element_hash **hash); // return move element
////Перемещение указанного элемента наверх, возврат копии его структуры

void change_in_list(struct element add, int name_delite, struct list list, struct element_hash **hash);
///Добавление add сверху, удаление элемента name_delite из списка(поиск его аддреса через хеш) это же когда удаляемый элемент попадает в LIR?
#endif