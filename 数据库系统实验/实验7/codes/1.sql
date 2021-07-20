use school
select count(*)
from choices inner join courses on choices.cid = courses.cid
where cname = 'C++'

select count(*)
from choices inner join courses on choices.cid = courses.cid
where cname = 'C++' and score >= 60

select count(*)
from choices inner join courses on choices.cid = courses.cid
where cname = 'C++' and score < 60
