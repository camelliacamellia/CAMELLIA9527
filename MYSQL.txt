-- 建表语句
-- 创建角色表
CREATE TABLE character_table (
    number INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL UNIQUE,  -- 确保name唯一
    race VARCHAR(20),
    height INT,
    energy VARCHAR(50),
    city VARCHAR(50),
    `force` VARCHAR(50),
    `rank` VARCHAR(50),
    introduce TEXT
);

-- 插入示例数据
INSERT INTO character_table (name, race, height, energy, city, `force`, `rank`, introduce)
VALUES 
    ('程咬全', '人类', 200, '武道', '长安城', '长安', '名将', '一身健美的肌肉，饱含铁血的男儿柔情，说...'),
    ('李世民', '人类', 200, '武道', '长安城', '长安', '名将', '一身健美的肌肉，饱含铁血的男儿柔情，说...');

-- 更新角色名字
UPDATE character_table
SET name = '程咬金'
WHERE name = '程咬全';

-- 创建技能表（添加character_name字段）
CREATE TABLE skills_table (
    skill_id INT AUTO_INCREMENT PRIMARY KEY,
    character_name VARCHAR(50) NOT NULL,  -- 使用角色名字
    skill_name VARCHAR(50) NOT NULL,
    skill_type VARCHAR(30),
    skill_description TEXT,
    power_level INT,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (character_name) REFERENCES character_table(name) ON DELETE CASCADE
);

-- 插入技能数据（示例，使用角色名字）
INSERT INTO skills_table (character_name, skill_name, skill_type, skill_description, power_level)
VALUES 
    ('程咬金', '三板斧', '近战武技', '程咬全的成名绝技，威力惊人但只有三招', 85),
    ('程咬金', '铁布衫', '防御功法', '运功时全身如铁，刀枪不入', 75),
    ('程咬金', '豪气干云', '气势技能', '战斗时激发豪迈气势，提升全队士气', 90);

-- 更新技能表中的角色名字
UPDATE skills_table
SET character_name = '程咬金'
WHERE character_name = '程咬全';

-- 创建关系表
CREATE TABLE relationship_table (
    relationship_id INT AUTO_INCREMENT PRIMARY KEY,
    character_name VARCHAR(50) NOT NULL,
    related_character_name VARCHAR(50) NOT NULL,
    relationship_type VARCHAR(50) NOT NULL,
    description TEXT,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    
    -- 外键约束
    FOREIGN KEY (character_name) 
        REFERENCES character_table(name),
    
    -- 相关角色外键约束
    FOREIGN KEY (related_character_name) 
        REFERENCES character_table(name),
    
    -- 确保没有自我关系
    CONSTRAINT chk_not_self_relationship 
        CHECK (character_name <> related_character_name)
);

-- 插入关系数据（示例）
INSERT INTO relationship_table (
    character_name,
    related_character_name,
    relationship_type, description
)
VALUES ('程咬金', '李世民', '主臣', '程咬全效忠唐太宗');

-- 更新关系表中的角色名字
UPDATE relationship_table
SET character_name = '程咬金'
WHERE character_name = '程咬全';