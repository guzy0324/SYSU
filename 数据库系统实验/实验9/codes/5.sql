use school
create table lead
(
    sid char(10),
    dept char(20),
    evaluator char(10),
    constraint PK__L primary key (sid, dept)
)
create table evaluate
(
    sid char(10),
    dept char(20),
    leader char(10),
    constraint PK__E primary key (sid, dept)
)
alter table lead add 
	constraint FK__L foreign key (evaluator, dept) references evaluate (sid, dept) on delete no action;
alter table evaluate add 
	constraint FK__E foreign key (leader, dept) references lead (sid, dept) on delete no action;