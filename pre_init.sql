-- pre init to be run before importing the data
BEGIN TRANSACTION;
-- sqlite ignores the size put in varchar()
-- but I put them there for my sake
CREATE TABLE voters(
	id integer primary key,
	county varchar(3),
	last_name varchar(30),
	first_name varchar(30),
	middle_name varchar(30),
	name_suffix varchar(5),
	is_private tinyint,
	addr_1 varchar(50),
	addr_2 varchar(40),
	city varchar(40),
	state varchar(2),
	zipcode varchar(10),
	mailing_addr_1 varchar(40),
	mailing_addr_2 varchar(40),
	mailing_addr_3 varchar(40),
	mailing_city varchar(40),
	mailing_state varchar(2),
	mailing_zip varchar(12),
	mailing_country varchar(40),
	gender char(1),
	race tinyint,
	dob varchar(10),
	dor varchar(10),
	party varchar(3),
	precinct varchar(6),
	precinct_group varchar(3),
	precinct_split varchar(6),
	precinct_suffix varchar(3),
	is_active varchar(3),
	congressional_district varchar(3),
	house_district varchar(3),
	senate_district varchar(3),
	county_commision_district varchar(3),
	school_board_district varchar(2),
	phone_area integer,
	phone integer,
	phone_ext integer,
	email_addr varchar(100)
);

CREATE TABLE race_codes(
	code integer primary key,
	description varchar(35)
);
INSERT INTO race_codes
	(code, description)
VALUES
	(1, 'American Indian or Alaska Native'),
	(2, 'Asian or Pacific Islander'),
	(3, 'Black'),
	(4, 'Hispanic'),
	(5, 'White'),
	(6, 'Other'),
	(7, 'Multi-racial'),
	(9, 'Unknown');

CREATE TABLE party_codes(
	id integer primary key,
	code varchar(3),
	description varchar(35)
);
INSERT INTO party_codes
	(code, description)
VALUES
	('cpf', 'Constitution Party of Florida'),
	('dem', 'Florida Democratic Party'),
	('eco', 'Ecology Party of Florida'),
	('gre', 'Green Party of Florida'),
	('ind', 'Independent Party of Florida'),
	('lpf', 'Libertarian Party of Florida'),
	('npa', 'No Party Affiliation'),
	('psl', 'Party for Socialism and Liberation - Florida'),
	('ref', 'Reform Party of Florida'),
	('rep', 'Republican Party of Florida ');

CREATE TABLE county_codes(
	id integer primary key,
	code varchar(3),
	description varchar(35)
);
INSERT INTO county_codes
	(code, description)
VALUES
	('ala', 'Alachua'),
	('ham', 'Hamilton'),
	('oke', 'Okeechobee'),
	('bak', 'Baker'),
	('har', 'Hardee'),
	('ora', 'Orange'),
	('bay', 'Bay'),
	('hen', 'Hendry'),
	('osc', 'Osceola'),
	('bra', 'Bradford'),
	('her', 'Hernando'),
	('pal', 'Palm Beach'),
	('bre', 'Brevard'),
	('hig', 'Highlands'),
	('pas', 'Pasco'),
	('bro', 'Broward'),
	('hil', 'Hillsborough'),
	('pin', 'Pinellas'),
	('cal', 'Calhoun'),
	('hol', 'Holmes'),
	('pol', 'Polk'),
	('cha', 'Charlotte'),
	('ind', 'Indian River'),
	('put', 'Putnam'),
	('cit', 'Citrus'),
	('jac', 'Jackson'),
	('san', 'Santa Rosa'),
	('cla', 'Clay'),
	('jef', 'Jefferson'),
	('sar', 'Sarasota'),
	('cll', 'Collier'),
	('laf', 'Lafayette'),
	('sem', 'Seminole'),
	('clm', 'Columbia'),
	('lak', 'Lake'),
	('stj', 'St. Johns'),
	('dad', 'Miami-Dade'),
	('lee', 'Lee'),
	('stl', 'St. Lucie'),
	('des', 'Desoto'),
	('leo', 'Leon'),
	('sum', 'Sumter'),
	('dix', 'Dixie'),
	('lev', 'Levy'),
	('suw', 'Suwannee'),
	('duv', 'Duval'),
	('lib', 'Liberty'),
	('tay', 'Taylor'),
	('esc', 'Escambia'),
	('mad', 'Madison'),
	('uni', 'Union'),
	('fla', 'Flagler'),
	('man', 'Manatee'),
	('vol', 'Volusia'),
	('fra', 'Franklin'),
	('mrn', 'Marion'),
	('wak', 'Wakulla'),
	('gad', 'Gadsden'),
	('mrt', 'Martin'),
	('wal', 'Walton'),
	('gil', 'Gilchrist'),
	('mon', 'Monroe'),
	('was', 'Washington'),
	('gla', 'Glades'),
	('nas', 'Nassau'),
	('gul', 'Gulf'),
	('oka', 'Okaloosa');

COMMIT;
