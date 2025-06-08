#! /usr/bin/python

class AttrDict(dict):
    def __getattr__(self, key):
        if key not in self:
            raise AttributeError(key) # essential for testing by hasattr
        return self[key]
    def __delattr__(self, key):
        if key not in self:
            raise AttributeError(key) # essential for testing by hasattr
        del self[key]
    def __setattr__(self, key, value):
        self[key] = value
def make_dict(**kwargs):
    return AttrDict(kwargs)

# файл разбиваю на логические строки в которых (\\\n - пробельный символ) + атрибут многострочного комментария + физич. номер строки, имя_файла
# строки разбиваю на токены (для детектирования многострочных комментариев) id, symbol, literal, пробелы-комменты - выбрасываем

# детектируем ifdef, ifndef, if, elif, endif и после них ставим message
# потом анализируем, какие message были напечатаны и комментируем ненапечатанные участки

AnAlIzE = 'AnAlIzE'

import re
import ast

def read_re(s,p,pattenr,r):
	match = re.match(pattenr, s[p.pos:])
	if match:
		r.match = [match.group()]+list(match.groups())
		p.pos += match.end()
		return True
	return False

def read_str(s, p, r):
	if read_re(s,p, r'([lL]?)("([^\\"]|\\[nrtvfab\\\'"?]|\\[0-9]{1,3}|\\x[0-9a-fA-F]{2})*")', r):
		r.type = 'str'# 'const wchar_t *' if r.match[1] in 'lL' else 'const char *'
		r.mod = r.match[1].lower()
		r.val = ast.literal_eval(r.match[2])
		r.repr = r.match[2]
		del r.match
		return True
	return False

def read_char(s, p, r):
	if read_re(s,p, r"([lL]?)('([^\\']|\\[nrtvfab\\'\"?]|\\[0-9]{1,3}|\\x[0-9a-fA-F]{2})+')", r):
		r.type = 'char'# 'wchar_t' if r.match[1] in 'lL' else 'char'
		r.mod = r.match[1].lower()
		r.val = ord(ast.literal_eval(r.match[2]))
		r.repr = r.match[2]
		del r.match
		return True
	return False

def read_int(s, p, r):
	if read_re(s,p, r'(0[0-7]*)([uU]?[lL]?[lL]?)', r):
		r.val = int(r.match[1], base=8)
	elif read_re(s,p, r'([1-9][0-9]*)([uU]?[lL]?[lL]?)', r):
		r.val = int(r.match[1])
	elif read_re(s,p, r'(0[xX][0-9a-fA-F]+)([uU]?[lL]?[lL]?)', r):
		r.val = int(r.match[1], base=16)
	if 'match' in r:
		r.repr = r.match[1]
		t = r.match[2].lower()
		del r.match
		r.type = 'int' # ' '.join((['unsigned'] if 'u' in t else []) + ['long']*t.count('l'))
		r.mod = t
		if r.type == '':
			r.type = 'int'
		return True
	return False

def read_float(s, p, r):
	if read_re(s,p, r'([+-]?\d+\.\d+([eE][+-]?\d+)?|[+-]?\d+[eE][+-]?\d+)([fFlL]?)', r):
		r.type = 'float' # if r.match[3] in 'fF' else 'long double' if r.match[3] in 'lL' else 'double'
		r.mod = r.match[3].lower()
		r.val = float(r.match[1])
		r.repr = r.match[1]
		del r.match
		return True
	return False

def read_literal(s, p, r):
	if read_float(s, p, r): return True
	if read_int(s, p, r): return True
	if read_char(s, p, r): return True
	if read_str(s, p, r): return True
	return False

def read_symbol(s, p, r):
	if p.pos>=len(s): return False
	if s[p.pos:p.pos+3] in ['>>=', '<<=']:
		r.type = 'sym'
		r.sym = s[p.pos:p.pos+3]
		p.pos+=3
		return True
	if s[p.pos:p.pos+2] in ['>>', '<<', '->', '++', '--', '+=', '-=', '*=', '/=', '%=', '&=', '^=', '|=', '==', '!=', '<=', '>=', '&&', '||']:
		r.type = 'sym'
		r.sym = s[p.pos:p.pos+2]
		p.pos+=2
		return True
	if s[p.pos] in '()[]{}<>.,;=+-*/%&|^#?:!~':
		r.type = 'sym'
		r.sym = s[p.pos]
		p.pos+=1
		return True
	return False

def read_spc(s, p, in_comment):
	if in_comment.b: return False
	if p.pos>=len(s): return False
	if s[p.pos] in ' \n\t\r\v\f':
		p.pos+=1
		return True
	if s[p.pos:].startswith('/*'):
		p.pos+=2
		in_comment.b = True
		read_comment_tail(s, p, in_comment)
		return True
	#if s[p.pos:].startswith('//UnIfDeF'):
	#	p.pos += len('//UnIfDeF')
	#	return True
	if s[p.pos:].startswith('//'):
		p.pos = len(s)
		return True
	return False

def read_spcs(s, p, in_comment):
	while read_spc(s, p, in_comment):
		pass

def read_comment_tail(s, p, in_comment):
	pp = s[p.pos:].find('*/')
	if pp == -1:
		p.pos = len(s)
	else:
		p.pos += pp+2
		in_comment.b = False

def read_id(s, p, r): 
	if read_re(s, p, r'[a-zA-Z$_][a-zA-Z$_0-9]*', r):
		r.type='id'
		r.id = r.match[0]
		del r.match
		return True
	return False

def read_token(s, p, r, in_comment):
	if in_comment.b:
		read_comment_tail(s, p, in_comment)
	if in_comment.b: return False
	read_spcs(s, p, in_comment)
	if in_comment.b: return False
	if read_symbol(s, p, r): return True # ведущие знаки литералов по началу считаем отдельно
	if read_literal(s, p, r): return True # префиксы/суффиксы могут быть восприняты как идентификаторы
	if read_id(s, p, r): return True
	return False

# r.type=='id', r.id
# r.type=='sym', r.sym
# r.type==('int'|'float'|'char'|'str'), r.mod, r.val, r.repr

STAGE = 1
FIRST_CHECK = False
DEBUG = 0
LINES = set()
VARS =  {}

def make_sym(sym):
	return make_dict(type='sym', sym=sym)

def add_analyze(fname):

	with open(fname, 'r', encoding='utf-8') as file:
		s = file.read()
		if FIRST_CHECK:
			if AnAlIzE in s:
				raise Exception(f'AnAlIzE in {fname}')
			if '//UnIfDeF' in s:
				raise Exception(f'//UnIfDeF in {fname}')
			if 'StRiNgIfY' in s:
				raise Exception(f'StRiNgIfY in {fname}')
			if 'ToStRiNg' in s:
				raise Exception(f'ToStRiNg in {fname}')

		content = list(enumerate(s.split('\n')))  # Читает весь файл в одну строку

	in_comment = make_dict(b=False)
	log_line = ''

	ids = set()

	ol = 0
	al = 0

	enabled = True

	with open(fname, 'w', encoding='utf-8') as file:
		for lnum, line in content:
			if log_line!='':
				log_line += '\n'+line
			else:
				log_line = line
			if line.endswith('\\'):
				continue
			in_line = log_line.replace('*///UnIfDeF','').replace('/*UnIfDeF','').replace('//UnIfDeF','')
			line = re.sub(r'\\\n','',in_line)
			log_line = ''
			if 'AnAlIzE' in line:
				al+=1
				continue

			# analyze of line
			p = make_dict(pos=0)
			r = make_dict()
			tokens = []
			start_in_comment = in_comment.b
			while read_token(line, p, r, in_comment):
				tokens.append(r)
				r = make_dict()
			if p.pos<len(line):
				raise Exception(f'Syntax error at {fname}:{lnum} in {repr(line[p.pos:])}')

			y = False
			if len(tokens)==3 and tokens[0] == make_sym('#') and tokens[1].type=='id' and (tokens[1].id=='ifdef' or tokens[1].id=='ifndef') and tokens[2].type=='id':
				ids.add(tokens[2].id)
				y = True
			if len(tokens)>2 and tokens[0] == make_sym('#') and tokens[1].type=='id' and (tokens[1].id=='if' or tokens[1].id=='elif'):
				for t in tokens[2:]:
					if t.type=='id' and t.id!='defined':
						ids.add(t.id)
				y = True
			if len(tokens)==2 and tokens[0] == make_sym('#') and tokens[1].type=='id' and (tokens[1].id=='endif' or tokens[1].id=='else'):
				y = True
			
			if enabled or y:
				print(in_line,file=file)
			else:
				if start_in_comment and not in_comment.b:
					print('*///UnIfDeF',in_line,file=file)
				elif not start_in_comment and in_comment.b:
					print('/*UnIfDeF',in_line,file=file)
				else:
					print('//UnIfDeF',in_line,file=file)
			
			if y:
				ol+=1
				if STAGE==1:
					print(f'#pragma message("enabled line {lnum+1+ol-al}") // source_line {lnum+1-al} AnAlIzE', file=file)
				if STAGE==2:
					#print(f'//UnIfDeF #pragma message("enabled line {lnum+1+ol-al}") // source_line {lnum+1-al} AnAlIzE', file=file)
					enabled = (fname,(lnum+1+ol-al)) in LINES

		if STAGE==1:
			print('#define StRiNgIfY(x) #x // AnAlIzE', file=file)
			print('#define ToStRiNg(x) StRiNgIfY(x) // AnAlIzE', file=file)
			for id in sorted(ids):
				print(f'#ifdef {id} // AnAlIzE', file=file)
				print(f'#pragma message("{id} = \'" ToStRiNg({id}) "\'") // AnAlIzE', file=file)
				print(f'#else // AnAlIzE', file=file)
				print(f'#pragma message("{id} not defined") // AnAlIzE', file=file)
				print(f'#endif // AnAlIzE', file=file)
		if STAGE==2:
			if fname in VARS:
				for n,v in VARS[fname].items():
					if v==-1:
						print(f'// {n} has diffent values // AnAlIzE', file=file)
					elif v is None:
						print(f'// {n} is undefined // AnAlIzE', file=file)
					else:
						print(f'// {n} = {v} // AnAlIzE', file=file)

import os.path

def read_log(fname):
	# clang only
	with open(fname, 'r', encoding='utf-8') as file:
		while (s:= file.readline()) != '':
			s = s.rstrip('\n')
			if m:=re.fullmatch(r'([^:]+):(\d+):\d+: warning: enabled line \d+ \[-W#pragma-messages\]',s):
				s2 = file.readline().rstrip('\n')
				if not s2.endswith('AnAlIzE'):
					print('ignore:')
					print(s)
					print(s2)
					continue
				f,l = os.path.normpath(m[1]), int(m[2])
				global LINES
				LINES.add((f,l))
			else:
				global VARS
				y = False
				if m:=re.fullmatch(r'([^:]+):(\d+):\d+: warning: ([a-zA-Z_0-9$]+) = \'(.*)\' \[-W#pragma-messages\]',s):
					f,l,n,v,y = os.path.normpath(m[1]),int(m[2]),m[3],m[4],True
				if m:=re.fullmatch(r'([^:]+):(\d+):\d+: warning: ([a-zA-Z_0-9$]+) not defined \[-W#pragma-messages\]',s):
					f,l,n,v,y = os.path.normpath(m[1]),int(m[2]),m[3],None,True # None=undefined
				if y:
					s2 = file.readline().rstrip('\n')
					if not s2.endswith('AnAlIzE'):
						print('ignore:')
						print(s)
						print(s2)
						continue

					if f not in VARS:
						VARS[f] = {}
					vars = VARS[f]
					if n in vars and vars[n]!=v:
						vars[n] = -1 # -1=различные значения
					else:
						vars[n] = v

if __name__ == '__main__':
	import sys

	for fname in sys.argv[1:]:
		if fname.startswith('--log='):
			read_log(fname[len('--log='):])
			STAGE = 2
		elif fname=='--help':
			print('run `add_analyze.py <all c/c++ sources and headers>`')
			print('it adds analitic macroses into code')
			print('after each #if #ifdef #ifndef #elif #else #endif to understand which lines will be compiled')
			print('also for all macroses used in it')
			print('')
			print('run `configure --cc=clang 2>&1 | tee log`')
			print('run `make 2>&1 | tee -a log`')
			print('to gather information from compiler output (also program will be compiled)')
			print('note that it (now) can understand only clang format output')
			print('(gcc falls if #pragma message are inside enum)')
			print()
			print('run `add_analyze.py --log=log <all c/c++ sources and headers>`')
			print('to comment unused blocks')
			print('and to print macroses\' values (used in #if...) at the end of each file')
			print()
			print('this utility not tested with modern c++ literals')
			print('also if an error occures in this script, file on which it works will be corrupted and should be restored from git')
		else:
			add_analyze(os.path.normpath(fname))
