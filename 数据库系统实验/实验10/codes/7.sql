use school
exec sp_unbindrule 'worker.[sage]'
insert into worker(number, name, sex, sage, department)
values('00003', '王浩', 'M', 101, '研发部')