DROP SCHEMA public CASCADE;
CREATE SCHEMA public;

CREATE TABLE departments (
  dep_id SERIAL PRIMARY KEY,
  name text
);

CREATE TABLE employees (
  emp_id SERIAL PRIMARY KEY,
  dep_id integer,
  manager_id integer,
  name text,
  salary integer
);

CREATE TABLE bonuses (
  bonus_id SERIAL PRIMARY KEY,
  emp_id integer,
  ga_id integer,
  amount integer,
  date time
);

CREATE TABLE bonuses (
  bonus_id SERIAL PRIMARY KEY,
  emp_id integer,
  ga_id integer,
  amount integer,
  date time
);

CREATE TABLE granting_authorities (
  ga_id SERIAL PRIMARY KEY,
  emp_id integer,
  dept_id integer
);

select d.name, x.total from (
  select sum(b.amount) as total, e.dep_id
  from bonuses b
  join employees e
  on e.emp_id = b.emp_id
  group by e.dep_id
) as x
join departments d
on x.dep_id = d.dep_id;

INSERT INTO departments (name)
SELECT md5(random()::text)
  FROM generate_series(1, 500)
;

INSERT INTO employees (dep_id, manager_id, name, salary)
SELECT random() * 500 + 1, random() * 500 + 1, md5(random()::text), random() * 100000 + 1
  FROM generate_series(1, 500)
;

INSERT INTO bonuses (emp_id, ga_id, amount, date)
SELECT random() * 500 + 1, random() * 500 + 1, random() * 10000 + 1, NOW() - '1 year'::INTERVAL * ROUND(RANDOM() * 100)
  FROM generate_series(1, 500)
;

INSERT INTO granting_authorities (emp_id, dept_id)
SELECT random() * 500 + 1, random() * 500 + 1
  FROM generate_series(1, 500)
;

-- select * from departments limit 1;
-- select * from employees limit 1;
-- select * from bonuses limit 1;
-- select * from granting_authorities limit 1;

