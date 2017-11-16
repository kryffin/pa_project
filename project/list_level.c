#include "header.h"

list_l list_l_empty ()
{
  return NULL;
}

list_l cons_list_l (level* lvl, list_l liste)
{
  list_l L = malloc(sizeof(struct list_level));
  if (L == NULL){
    printf("error allocation list_l\n");
    exit(EXIT_FAILURE);
  }
  L->head = lvl;
  L->next = liste;

  return L;
}

level* head_list_l (list_l liste)
{
  if (!is_empty_list_l(liste)){
    return liste->head;
  } else {
    printf("head sur list_l vide exit\n");
    exit (EXIT_FAILURE);
  }
}

list_l next_list_l (list_l liste)
{
  if (!is_empty_list_l(liste)){
    return liste->next;
  } else {
    printf("next sur list_l vide exit\n");
    exit (EXIT_FAILURE);
  }
}

bool is_empty_list_l (list_l L)
{
  return L == NULL;
}
