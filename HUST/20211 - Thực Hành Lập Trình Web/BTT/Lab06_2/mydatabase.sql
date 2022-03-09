create database business_service;

use business_service;

create table categories(
    category_id varchar(10) not null primary key,
    title varchar(50) not null,
    description varchar(50)
);

create table businesses(
    business_id int(11) auto_increment primary key,
    name varchar(50) not null,
    address varchar(50),
    city varchar(50),
    telephone varchar(10),
    url varchar(50)
);

create table biz_categories(
    business_id int(11) auto_increment,
    category_id varchar(10),
    primary key (business_id, category_id),
    foreign key (business_id) references businesses(business_id),
    foreign key (category_id) references categories(category_id)
)