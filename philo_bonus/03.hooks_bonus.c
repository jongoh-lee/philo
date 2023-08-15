#include "./main_bonus.h"

void	sem_open_hoook(sem_t **sema, const char *str, unsigned int sema_num)
{
	*sema = sem_open(str, O_CREAT | O_EXCL, 0644, sema_num);
	if (*sema == SEM_FAILED)
		on_error(SEMA);
}
