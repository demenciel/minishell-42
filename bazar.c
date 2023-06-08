
printf ("i start = %d\n", ms->i);

printf ("i end = %d\n", ms->i);


while (ms->line[ms->i] && ms->line[ms->i] > 32 &&
	ms->line[ms->i] != 124 && ms->line[ms->i] != 62 &&ms->line[ms->i + 1] != 36 &&
	ms->line[ms->i] != 60 && ms->line[ms->i] != 39 && ms->line[ms->i] != 34)
		ms->i++;
	if (ms->line[ms->i + 1] == 36)
		end = ms->i++;
	end = ms->i;