use school
create table mutual_help
(
    sid char(10),
    sname char(8),
    target char(10) references mutual_help (sid) on delete no action,
    constraint PK_MH primary key (sid)
)