use school
select distinct grade
from students
where grade >= all (select grade
                    from students
                    where grade is not null)
