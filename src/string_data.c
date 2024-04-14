#include "string_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StringData string_new(size_t reserve)
{
	if (reserve >= STRING_DATA_MAX_SIZE || reserve == 0)
		reserve = STRING_DATA_MAX_SIZE;

	StringData sd = {0, 0, 0};
	sd.p_data = calloc(reserve, sizeof(char));

	if (sd.p_data == NULL) {
		fprintf(stderr, "Error: string_new: could not allocate memory");
		return sd;
	}
	sd.m_p_data_end = sd.p_data;
	sd.m_p_data_size = reserve;
	return sd;
}

void string_free(StringData *sd)
{
	if (sd == NULL || sd->p_data == NULL)
		return;

	free(sd->p_data);
	sd->p_data = NULL;
	sd->m_p_data_end = NULL;
	sd->m_p_data_size = 0;
}

int string_squeeze(StringData *sd)
{
	size_t len = strlen(sd->p_data) + 1;
	if (len >= sd->m_p_data_size)
		return -1;

	char *buf = calloc(len, sizeof(char));
	if (buf == NULL) {
		fprintf(stderr, "Error: string_squeeze: could not allocate memory");
		return -1;
	}
	
	strcpy(buf, sd->p_data);

	string_free(sd);
	sd->p_data = buf;
	sd->m_p_data_end = buf + len - 1;
	sd->m_p_data_size = len;

	return 0;
}

int string_push(StringData *sd, char c)
{
	if (sd == NULL || sd->p_data == NULL)
		return -1;

	if (sd->m_p_data_end - sd->p_data >= sd->m_p_data_size)
		return -1;

	*(sd->m_p_data_end) = c;
	sd->m_p_data_end++;

	return 0;
}