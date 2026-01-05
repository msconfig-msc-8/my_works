#include <iostream>
#include <string>

// Exceptions
#include "exceptions/Exceptions.hpp"

// Users
#include "models/users/User.hpp"
#include "models/users/Profile.hpp"
#include "models/users/FriendList.hpp"
#include "models/users/FriendRequest.hpp"
#include "models/users/Follower.hpp"
#include "models/users/BlockedUser.hpp"
#include "models/users/UserStatus.hpp"
#include "models/users/Location.hpp"

// Content
#include "models/content/Post.hpp"
#include "models/content/Comment.hpp"
#include "models/content/Like.hpp"
#include "models/content/Share.hpp"
#include "models/content/Story.hpp"
#include "models/content/StoryViewer.hpp"
#include "models/content/Album.hpp"
#include "models/content/Photo.hpp"
#include "models/content/Video.hpp"
#include "models/content/Tag.hpp"
#include "models/content/Mention.hpp"
#include "models/content/Reaction.hpp"

// Messaging
#include "models/messaging/Message.hpp"
#include "models/messaging/Chat.hpp"
#include "models/messaging/GroupChat.hpp"
#include "models/messaging/ChatMember.hpp"
#include "models/messaging/Attachment.hpp"
#include "models/messaging/Notification.hpp"
#include "models/messaging/NotificationSettings.hpp"
#include "models/messaging/VoiceMessage.hpp"

// Groups
#include "models/groups/Group.hpp"
#include "models/groups/GroupMember.hpp"
#include "models/groups/GroupPost.hpp"
#include "models/groups/Page.hpp"
#include "models/groups/PageAdmin.hpp"
#include "models/groups/Event.hpp"
#include "models/groups/EventAttendee.hpp"
#include "models/groups/Poll.hpp"

// Security
#include "models/security/Settings.hpp"
#include "models/security/PrivacySettings.hpp"
#include "models/security/Session.hpp"
#include "models/security/LoginHistory.hpp"
#include "models/security/TwoFactorAuth.hpp"
#include "models/security/Report.hpp"

// Analytics
#include "models/analytics/ProfileStats.hpp"
#include "models/analytics/PostStats.hpp"
#include "models/analytics/ActivityLog.hpp"
#include "models/analytics/SearchHistory.hpp"
#include "models/analytics/ContentRecommendation.hpp"
#include "models/analytics/TrendingTopic.hpp"

// Monetization
#include "models/monetization/Advertisement.hpp"
#include "models/monetization/Wallet.hpp"

/**
 * @brief Демонстрация работы социальной сети
 */
int main() {
    std::cout << "=== Социальная сеть - Демонстрация ===" << std::endl;
    std::cout << std::endl;

    // Создание пользователей
    User user1("1", "ivan_petrov", "ivan@example.com", "hash123");
    User user2("2", "anna_sidorova", "anna@example.com", "hash456");
    
    std::cout << "Создан пользователь: " << user1.getUsername() << std::endl;
    std::cout << "Создан пользователь: " << user2.getUsername() << std::endl;

    // Создание профилей
    Profile profile1(user1.getId(), "Иван", "Петров");
    profile1.updateBio("Разработчик из Москвы");
    
    Profile profile2(user2.getId(), "Анна", "Сидорова");
    profile2.updateBio("Дизайнер");

    std::cout << "Профиль: " << profile1.getFullName() << " - " << profile1.getBio() << std::endl;

    // Аутентификация
    try {
        user1.authenticate("hash123");
        std::cout << user1.getUsername() << " успешно вошёл в систему" << std::endl;
    } catch (const InvalidCredentialsException& e) {
        std::cout << "Ошибка входа: " << e.what() << std::endl;
    }

    // Подписка
    Follower follower(user2.getId(), user1.getId());
    std::cout << user2.getUsername() << " подписался на " << user1.getUsername() << std::endl;

    // Создание поста
    Post post("p1", user1.getId(), "Привет, мир! Это мой первый пост.");
    std::cout << "Создан пост: " << post.getContent() << std::endl;

    // Комментарий
    Comment comment("c1", post.getId(), user2.getId(), "Отличный пост!");
    std::cout << "Комментарий: " << comment.getText() << std::endl;

    // Лайк
    Like like("l1", user2.getId(), post.getId(), LikeTargetType::POST);
    std::cout << "Лайк от: " << like.getUserId() << std::endl;

    // Статистика поста
    PostStats postStats(post.getId());
    postStats.incrementLikes();
    postStats.incrementComments();
    postStats.incrementViews();
    std::cout << "Статистика поста - Лайки: " << postStats.getLikesCount() 
              << ", Комментарии: " << postStats.getCommentsCount() << std::endl;

    // Создание группы
    Group group("g1", "Программисты C++", user1.getId());
    group.addMember(user2.getId());
    std::cout << "Создана группа: " << group.getName() 
              << " (" << group.getMemberCount() << " участников)" << std::endl;

    // Кошелёк и перевод денег
    Wallet wallet1(user1.getId());
    Wallet wallet2(user2.getId());
    
    wallet1.deposit(1000.0, "Начальный депозит");
    std::cout << "Баланс " << user1.getUsername() << ": " << wallet1.getBalance() << " RUB" << std::endl;

    try {
        wallet1.transfer(wallet2, 250.0, "Перевод другу");
        std::cout << "Перевод 250 RUB выполнен успешно" << std::endl;
        std::cout << "Баланс " << user1.getUsername() << ": " << wallet1.getBalance() << " RUB" << std::endl;
        std::cout << "Баланс " << user2.getUsername() << ": " << wallet2.getBalance() << " RUB" << std::endl;
    } catch (const InsufficientBalanceException& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    // Личные сообщения
    Message message("m1", user1.getId(), user2.getId(), "Привет! Как дела?");
    std::cout << "Отправлено сообщение: " << message.getContent() << std::endl;

    // Уведомление
    Notification notification("n1", user2.getId(), NotificationType::MESSAGE, 
                              "Новое сообщение от " + user1.getUsername());
    std::cout << "Уведомление: " << notification.getMessage() << std::endl;

    std::cout << std::endl;
    std::cout << "=== Демонстрация завершена ===" << std::endl;

    return 0;
}
