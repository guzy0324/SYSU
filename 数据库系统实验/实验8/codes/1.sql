use school
create table class(class_id varchar(4) not null unique,
    name varchar(10),
    department varchar(20),
    primary key (class_id))
