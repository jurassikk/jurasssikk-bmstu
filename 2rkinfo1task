
-- Создание таблиц
CREATE TABLE students (
    student_id SERIAL PRIMARY KEY,
    full_name VARCHAR(100) NOT NULL,
    group_number VARCHAR(20) NOT NULL
);

CREATE TABLE subjects (
    subject_id SERIAL PRIMARY KEY,
    subject_name VARCHAR(100) NOT NULL
);

CREATE TABLE grades (
    grade_id SERIAL PRIMARY KEY,
    student_id INTEGER REFERENCES students(student_id) ON DELETE CASCADE,
    subject_id INTEGER REFERENCES subjects(subject_id) ON DELETE CASCADE,
    grade INTEGER CHECK (grade >= 1 AND grade <= 5),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE attendance (
    attendance_id SERIAL PRIMARY KEY,
    student_id INTEGER REFERENCES students(student_id) ON DELETE CASCADE,
    date_attended DATE NOT NULL,
    status VARCHAR(20) CHECK (status IN ('присутствовал', 'отсутствовал', 'опоздал'))
);

CREATE TABLE notes (
    note_id SERIAL PRIMARY KEY,
    student_id INTEGER REFERENCES students(student_id) ON DELETE CASCADE,
    note_text TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Наполнение данных
INSERT INTO students (full_name, group_number) VALUES
('Иванов Иван Иванович', 'ИТ-101'),
('Петров Петр Петрович', 'ИТ-101'),
('Сидорова Анна Сергеевна', 'ИТ-101'),
('Кузнецова Мария Дмитриевна', 'ИТ-101'),
('Смирнов Алексей Викторович', 'ИТ-101'),
('Федоров Дмитрий Александрович', 'ИТ-101');

INSERT INTO subjects (subject_name) VALUES
('Математический анализ'),
('Аналитическая геометрия'),
('Информатика');

INSERT INTO grades (student_id, subject_id, grade) VALUES
(1, 1, 5), (1, 2, 4), (1, 3, 5), (1, 1, 4), (1, 2, 5), (1, 3, 5),
(2, 1, 3), (2, 2, 4), (2, 3, 3), (2, 1, 4), (2, 2, 3), (2, 3, 4),
(3, 1, 5), (3, 2, 5), (3, 3, 5), (3, 1, 5), (3, 2, 5), (3, 3, 5),
(4, 1, 4), (4, 2, 4), (4, 3, 4), (4, 1, 4), (4, 2, 4), (4, 3, 4),
(5, 1, 3), (5, 2, 3), (5, 3, 4), (5, 1, 3), (5, 2, 4), (5, 3, 4),
(6, 1, 2), (6, 2, 3), (6, 3, 2), (6, 1, 3), (6, 2, 3), (6, 3, 3);

INSERT INTO attendance (student_id, date_attended, status) VALUES
(1, '2024-01-15', 'присутствовал'),
(2, '2024-01-15', 'опоздал'),
(3, '2024-01-15', 'присутствовал'),
(4, '2024-01-15', 'присутствовал'),
(5, '2024-01-15', 'отсутствовал'),
(6, '2024-01-15', 'присутствовал'),
(1, '2024-01-16', 'присутствовал'),
(2, '2024-01-16', 'присутствовал'),
(3, '2024-01-16', 'присутствовал'),
(4, '2024-01-16', 'опоздал'),
(5, '2024-01-16', 'присутствовал'),
(6, '2024-01-16', 'отсутствовал');

INSERT INTO notes (student_id, note_text) VALUES
(1, 'Отличник по всем предметам. Любит информатику.'),
(2, 'Хорошо работает в команде. Прогресс по информатике.'),
(3, 'Лучший студент группы. Отличник по всем предметам.'),
(4, 'Стабильно хорошие оценки. Нужна помощь по информатике.'),
(5, 'Средняя успеваемость. Редко посещает занятия по информатике.'),
(6, 'Требуется дополнительная помощь. Плохо успевает по информатике.');

-- Индексы
CREATE INDEX idx_students_group ON students(group_number);
CREATE INDEX idx_grades_student ON grades(student_id);
CREATE EXTENSION IF NOT EXISTS pg_trgm;
CREATE INDEX idx_notes_note_text_gin ON notes USING gin(note_text gin_trgm_ops);

-- Представления
CREATE VIEW student_avg_grades AS
SELECT 
    s.student_id,
    s.full_name,
    s.group_number,
    ROUND(AVG(g.grade)::numeric, 2) as average_grade,
    COUNT(g.grade_id) as total_grades
FROM students s
LEFT JOIN grades g ON s.student_id = g.student_id
GROUP BY s.student_id, s.full_name, s.group_number
ORDER BY average_grade DESC NULLS LAST;

-- Транзакция
BEGIN;
INSERT INTO students (full_name, group_number) 
VALUES ('Новиков Артем Игоревич', 'ИТ-101');
INSERT INTO grades (student_id, subject_id, grade) VALUES
(7, 1, 4), (7, 2, 5), (7, 3, 4);
INSERT INTO attendance (student_id, date_attended, status) VALUES
(7, '2024-01-15', 'присутствовал'),
(7, '2024-01-16', 'присутствовал');
INSERT INTO notes (student_id, note_text) 
VALUES (7, 'Новый студент. Хорошо проявляет себя на занятиях по информатике.');
COMMIT;

-- Запросы
WITH student_ranks AS (
    SELECT 
        student_id,
        full_name,
        group_number,
        ROW_NUMBER() OVER (ORDER BY student_id) as rn
    FROM students
    WHERE group_number = 'ИТ-101'
),
target_rank AS (
    SELECT rn FROM student_ranks WHERE student_id = 3
)
SELECT student_id, full_name, group_number
FROM student_ranks
WHERE rn BETWEEN (SELECT rn FROM target_rank) - 2 
              AND (SELECT rn FROM target_rank) + 3
AND student_id != 3
ORDER BY rn;

SELECT * FROM student_avg_grades WHERE student_id = 3;

SELECT 
    s.subject_name,
    ROUND(AVG(g.grade)::numeric, 2) as average_grade,
    COUNT(g.grade_id) as total_grades
FROM subjects s
JOIN grades g ON s.subject_id = g.subject_id
WHERE s.subject_name = 'Информатика'
GROUP BY s.subject_id, s.subject_name;

SELECT 
    n.note_id,
    s.full_name,
    n.note_text,
    n.created_at
FROM notes n
JOIN students s ON n.student_id = s.student_id
WHERE n.note_text ILIKE '%информатик%'
ORDER BY n.created_at DESC;

BEGIN;
UPDATE attendance
SET status = 'отсутствовал'
WHERE student_id = 1 
AND date_attended = '2024-01-15';
COMMIT;
