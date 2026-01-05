# Социальная сеть - Лабораторная работа №2

Модель социальной сети на языке C++.

## Статистика проекта

| Метрика | Количество |
|---------|------------|
| Классы | 50 |
| Поля | 155 |
| Методы (поведения) | 112 |
| Ассоциации классов | 35 |
| Исключения | 12 |

## Структура проекта

```
/
├── src/
│   ├── main.cpp                    # Демонстрационная программа
│   ├── exceptions/
│   │   └── Exceptions.hpp          # 12 персональных исключений
│   └── models/
│       ├── users/                  # Классы пользователей (8)
│       ├── content/                # Классы контента (12)
│       ├── messaging/              # Классы сообщений (8)
│       ├── groups/                 # Классы групп (8)
│       ├── security/               # Классы безопасности (6)
│       ├── analytics/              # Классы аналитики (6)
│       └── monetization/           # Классы монетизации (2)
├── tests/
│   ├── tests.cpp                   # Unit-тесты
│   └── doctest.h                   # Тестовый фреймворк
├── Makefile                        # Сборка проекта
├── .gitignore                      # Игнорируемые файлы
└── README.md                       # Этот файл
```



---

## Классы

### Исключения (12)

| Класс | Поля | Методы | Ассоциации |
|-------|------|--------|------------|
| SocialNetworkException | 1 | 2 | → std::exception |
| UserNotFoundException | 0 | 1 | → SocialNetworkException |
| InvalidCredentialsException | 0 | 1 | → SocialNetworkException |
| DuplicateEmailException | 0 | 1 | → SocialNetworkException |
| PostNotFoundException | 0 | 1 | → SocialNetworkException |
| AccessDeniedException | 0 | 1 | → SocialNetworkException |
| MessageNotFoundException | 0 | 1 | → SocialNetworkException |
| InvalidContentException | 0 | 1 | → SocialNetworkException |
| GroupNotFoundException | 0 | 1 | → SocialNetworkException |
| AlreadyFriendsException | 0 | 1 | → SocialNetworkException |
| BlockedUserException | 0 | 1 | → SocialNetworkException |
| InsufficientBalanceException | 0 | 1 | → SocialNetworkException |

---

### Пользователи (8)

| Класс | Поля | Методы | Ассоциации |
|-------|------|--------|------------|
| User | 6 | 7 | → Profile, Settings |
| Profile | 7 | 9 | → User |
| FriendList | 3 | 9 | → User |
| FriendRequest | 4 | 6 | → User |
| Follower | 4 | 4 | → User |
| BlockedUser | 5 | 5 | → User |
| UserStatus | 4 | 6 | → User |
| Location | 4 | 5 | → |

---

### Контент (12)

| Класс | Поля | Методы | Ассоциации |
|-------|------|--------|------------|
| Post | 8 | 9 | → User, Comment, Like |
| Comment | 8 | 7 | → Post, User |
| Like | 5 | 3 | → User |
| Share | 5 | 3 | → User, Post |
| Story | 7 | 7 | → User, StoryViewer |
| StoryViewer | 3 | 3 | → Story, User |
| Album | 8 | 8 | → User, Photo |
| Photo | 7 | 5 | → Album |
| Video | 8 | 6 | → User |
| Tag | 3 | 5 | → |
| Mention | 6 | 4 | → User |
| Reaction | 5 | 4 | → User |

---

### Сообщения (8)

| Класс | Поля | Методы | Ассоциации |
|-------|------|--------|------------|
| Message | 7 | 6 | → User, Chat |
| Chat | 5 | 7 | → User, Message |
| GroupChat | 6 | 8 | → User |
| ChatMember | 5 | 6 | → Chat, User |
| Attachment | 7 | 4 | → Message |
| Notification | 7 | 6 | → User |
| NotificationSettings | 9 | 12 | → User |
| VoiceMessage | 7 | 4 | → User, Message |

---

### Группы (8)

| Класс | Поля | Методы | Ассоциации |
|-------|------|--------|------------|
| Group | 8 | 9 | → User, GroupMember |
| GroupMember | 4 | 7 | → Group, User |
| GroupPost | 7 | 6 | → Group, User |
| Page | 10 | 8 | → User |
| PageAdmin | 4 | 5 | → Page, User |
| Event | 11 | 9 | → User, Location |
| EventAttendee | 4 | 7 | → Event, User |
| Poll | 9 | 8 | → User |

---

### Безопасность (6)

| Класс | Поля | Методы | Ассоциации |
|-------|------|--------|------------|
| Settings | 6 | 8 | → User |
| PrivacySettings | 7 | 10 | → User |
| Session | 8 | 8 | → User |
| LoginHistory | 6 | 5 | → User |
| TwoFactorAuth | 5 | 7 | → User |
| Report | 9 | 8 | → User |

---

### Аналитика (6)

| Класс | Поля | Методы | Ассоциации |
|-------|------|--------|------------|
| ProfileStats | 6 | 10 | → User |
| PostStats | 6 | 10 | → Post |
| ActivityLog | 6 | 4 | → User |
| SearchHistory | 2 | 5 | → User |
| ContentRecommendation | 5 | 8 | → User, Post |
| TrendingTopic | 6 | 7 | → Tag |

---

### Монетизация (2)

| Класс | Поля | Методы | Ассоциации |
|-------|------|--------|------------|
| Advertisement | 13 | 11 | → User |
| Wallet | 5 | 9 | → User |

---

## Примеры поведений (методов)

1. **authenticate** - аутентификация пользователя
2. **logout** - выход из системы
3. **updateBio** - обновление биографии
4. **addFriend** - добавление друга
5. **removeFriend** - удаление друга
6. **acceptRequest** - принятие запроса в друзья
7. **follow** - подписка на пользователя
8. **unfollow** - отписка от пользователя
9. **block** - блокировка пользователя
10. **unblock** - разблокировка
11. **updateStatus** - обновление статуса
12. **getDistance** - расчёт расстояния между локациями
13. **create** (Post) - создание публикации
14. **edit** (Post) - редактирование публикации
15. **deletePost** - удаление публикации
16. **addComment** - добавление комментария
17. **reply** - ответ на комментарий
18. **addLike** - добавление лайка
19. **removeLike** - удаление лайка
20. **sharePost** - репост публикации
21. **createStory** - создание истории
22. **viewStory** - просмотр истории
23. **createAlbum** - создание альбома
24. **addPhoto** - добавление фото
25. **uploadVideo** - загрузка видео
26. **playVideo** - воспроизведение видео
27. **sendMessage** - отправка сообщения
28. **markAsRead** - отметить как прочитанное
29. **createChat** - создание чата
30. **addMember** (GroupChat) - добавление участника
31. **removeMember** - удаление участника
32. **sendNotification** - отправка уведомления
33. **createGroup** - создание группы
34. **joinGroup** - вступление в группу
35. **leaveGroup** - выход из группы
36. **promote** - повышение роли
37. **demote** - понижение роли
38. **createPage** - создание страницы
39. **followPage** - подписка на страницу
40. **createEvent** - создание мероприятия
41. **attendEvent** - участие в мероприятии
42. **createPoll** - создание опроса
43. **vote** - голосование в опросе
44. **updateSettings** - обновление настроек
45. **makePrivate** - сделать профиль приватным
46. **makePublic** - сделать профиль публичным
47. **createSession** - создание сессии
48. **terminateSession** - завершение сессии
49. **enable2FA** - включение двухфакторной аутентификации
50. **verify2FA** - проверка кода 2FA
51. **createReport** - создание жалобы
52. **resolveReport** - рассмотрение жалобы
53. **incrementFollowers** - увеличение счётчика подписчиков
54. **getEngagementRate** - расчёт вовлечённости
55. **logActivity** - запись активности
56. **addSearch** - добавление поиска в историю
57. **clearHistory** - очистка истории
58. **generateRecommendations** - генерация рекомендаций
59. **calculateTrendingScore** - расчёт трендовости
60. **createAd** - создание рекламы
61. **displayAd** - показ рекламы
62. **trackClick** - отслеживание клика
63. **deposit** - пополнение баланса
64. **withdraw** - снятие средств
65. **transfer** - перевод денег между кошельками
66. **getBalance** - получение баланса
... и другие

---

## Примеры ассоциаций

1. **User** → **Profile** (один к одному)
2. **User** → **Settings** (один к одному)
3. **User** → **FriendList** (один к одному)
4. **Post** → **User** (автор)
5. **Post** → **Comment** (один ко многим)
6. **Post** → **Like** (один ко многим)
7. **Comment** → **User** (автор)
8. **Comment** → **Post** (родительский пост)
9. **Message** → **User** (отправитель)
10. **Message** → **User** (получатель)
11. **Chat** → **User** (участники)
12. **Chat** → **Message** (один ко многим)
13. **Group** → **User** (владелец)
14. **Group** → **GroupMember** (один ко многим)
15. **GroupMember** → **User** (ссылка)
16. **Page** → **User** (владелец)
17. **PageAdmin** → **Page** (ссылка)
18. **PageAdmin** → **User** (ссылка)
19. **Event** → **User** (организатор)
20. **Event** → **Location** (место проведения)
21. **EventAttendee** → **Event** (ссылка)
22. **EventAttendee** → **User** (ссылка)
23. **Story** → **User** (автор)
24. **StoryViewer** → **Story** (ссылка)
25. **StoryViewer** → **User** (просмотревший)
26. **Album** → **User** (владелец)
27. **Album** → **Photo** (один ко многим)
28. **Notification** → **User** (получатель)
29. **Session** → **User** (владелец)
30. **Wallet** → **User** (владелец)
31. **Advertisement** → **User** (рекламодатель)
32. **ProfileStats** → **User** (владелец)
33. **PostStats** → **Post** (публикация)
34. **SearchHistory** → **User** (владелец)
35. **ContentRecommendation** → **User**, **Post**

---





