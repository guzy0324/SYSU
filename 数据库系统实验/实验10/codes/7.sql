use school
exec sp_unbindrule 'worker.[sage]'
insert into worker(number, name, sex, sage, department)
values('00003', '����', 'M', 101, '�з���')