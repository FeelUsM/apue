#! /usr/bin/python

# делает читабельным вывод make -pn

import re

global_s = None
def getline():
	global global_s
	if global_s is not None:
		s = global_s
		global_s = None
		return s
	else:
		try:
			return input()
		except EOFError:
			return None
def ungetline(s):
	global global_s
	assert global_s is None
	global_s = s
	

# -------

def read_vars():
	assert (s:=getline()) == '# Переменные' and s is not None
	print(s)
	assert getline()=='' and s is not None

	default_vars = []
	env_vars = []
	auto_vars = []
	mf_vars = []
	other_vars = []
	while (s:=getline()) != '# состояние переменных в хеш-таблице:' and s is not None:
		assert (s2:= getline()) != '' and s is not None
		if s=='# по умолчанию':
			default_vars.append(s2)
		elif s=='# определена в среде':
			env_vars.append(s2)
		elif s=='# автоматическая':
			auto_vars.append(s2)
		elif s.startswith('# make-файл'):
			m = re.match('# make-файл \(из «(.+)», строка (\d+)\)',s)
			if m is not None:
				l = int(m[2])
				mf_vars.append((m[1],l,s2))
			else:
				other_vars.append((s,s2))
		else:
			other_vars.append((s,s2))
	end_s = s

	mf_vars = sorted(mf_vars,key=lambda p: (p[0],p[1]))

	for name,ss in [('# переменные среды',env_vars), ('# по умолчанию',default_vars), ('# автоматические',auto_vars)]:
		print(name)
		for s2 in ss:
			print('\t'+s2)
	if len(other_vars)>0:
		print('# прочие')
		for s,s2 in other_vars:
			print('\t'+s)
			print('\t'+s2)
	print('# make-файл')
	for f,l,s2 in mf_vars:
		print(f'\t# make-файл (из «{f}», строка {l})')
		print('\t'+s2)

	print(end_s)

def read_dirs():
	assert (s:=getline()) == '# Каталоги' and s is not None
	print(s)
	assert getline()=='' and s is not None
	x_unattainable_goals = []
	no_unattainable_goals = []
	no_stat = []
	while (s:=getline()) != '' and s is not None:
		if s.endswith('невозможно получить сведения вызовом stat.'):
			no_stat.append(s)
		elif s.endswith('нет недостижимых целей.'):
			no_unattainable_goals.append(s)
		else:
			x_unattainable_goals.append(s)

	for s in x_unattainable_goals:
		print('\t'+s)
	print('-----')
	for s in no_unattainable_goals:
		print('\t'+s)
	print('-----')
	for s in no_stat:
		print('\t'+s)
	print()

def read_ambigous():
	assert (s:=getline()) == '# Неявные правила' and s is not None
	print(s)
	while not (s:=getline()).startswith('# Неявных правил:') and s is not None:
		print('\t'+s)
	print(s)

def read_files():
	assert (s:=getline()) == '# Файлы' and s is not None
	print(s)
	assert getline()=='' and s is not None
	phony = []
	updated_goal = []
	updated_nogoal = []
	noupdated_goal = []
	noupdated_nogoal_nobuiltin = []
	noupdated_nogoal_builtin_withcommand = []
	noupdated_nogoal_builtin_withoutcommand = []

	br = False
	while not br:
		ls = [] # list of strings
		while (s:=getline()) != '' and s is not None:
			if s=='# состояние файлов хеш-таблицы:':
				assert len(ls)==0 , ls
				end_s = s
				br = True
				break
			ls.append(s)
		if br:
			break

		if '#  Псевдоцель (зависимость от .PHONY).' in ls:
			phony.append(ls)
		elif '#  Файл был обновлён.' in ls:
			if '# Не является целью:' not in ls:
				updated_goal.append(ls)
			else:
				updated_nogoal.append(ls)
		elif '# Не является целью:' not in ls:
			noupdated_goal.append(ls)
		elif '# Встроенное правило' not in ls:
			noupdated_nogoal_nobuiltin.append(ls)
		elif ls[-1].startswith('#'):
			noupdated_nogoal_builtin_withoutcommand.append(ls)
		else:
			noupdated_nogoal_builtin_withcommand.append(ls)

	for lss in [phony, updated_goal, updated_nogoal, noupdated_goal, noupdated_nogoal_nobuiltin, noupdated_nogoal_builtin_withcommand, noupdated_nogoal_builtin_withoutcommand]:
		if lss != phony:
			print('-----')
		for ls in lss:
			a = False
			for s in ls:
				assert type(s) is str, ls
				if s=='# автоматическая':
					print('\t\t'+s)
					a = True
				elif a:
					print('\t\t'+s)
					a = False
				else:
					print('\t'+s)
			print()		
	print(end_s)

def read_run():
	while (s:=getline()) != '# Переменные' and s is not None:
		print(s)
	ungetline(s)
	read_vars()

	while (s:=getline()) != '# Каталоги' and s is not None:
		print(s)
	ungetline(s)
	read_dirs()

	while (s:=getline()) != '# Неявные правила' and s is not None:
		print(s)
	ungetline(s)
	read_ambigous()

	while (s:=getline()) != '# Файлы' and s is not None:
		print(s)
	ungetline(s)
	read_files()

	while not (s:=getline()).startswith('# Печать базы данных Make завершена') and s is not None:
		print(s)
	print(s)

read_run()
while (s:=getline()) is not None and s!='':
	ungetline(s)
	print('========================================================')
	read_run()

while (s:=getline()) is not None:
	if s!='':
		print('?\t'+s)
	else:
		print()
