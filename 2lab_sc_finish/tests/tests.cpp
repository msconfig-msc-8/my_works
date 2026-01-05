#include "doctest.h"

// Exceptions
#include "../src/exceptions/Exceptions.hpp"

// Users
#include "../src/models/users/User.hpp"
#include "../src/models/users/Profile.hpp"
#include "../src/models/users/FriendList.hpp"
#include "../src/models/users/FriendRequest.hpp"
#include "../src/models/users/Follower.hpp"
#include "../src/models/users/BlockedUser.hpp"
#include "../src/models/users/UserStatus.hpp"
#include "../src/models/users/Location.hpp"

// Content
#include "../src/models/content/Post.hpp"
#include "../src/models/content/Comment.hpp"
#include "../src/models/content/Like.hpp"
#include "../src/models/content/Share.hpp"
#include "../src/models/content/Story.hpp"
#include "../src/models/content/StoryViewer.hpp"
#include "../src/models/content/Album.hpp"
#include "../src/models/content/Photo.hpp"
#include "../src/models/content/Video.hpp"
#include "../src/models/content/Tag.hpp"
#include "../src/models/content/Mention.hpp"
#include "../src/models/content/Reaction.hpp"

// Messaging
#include "../src/models/messaging/Message.hpp"
#include "../src/models/messaging/Chat.hpp"
#include "../src/models/messaging/GroupChat.hpp"
#include "../src/models/messaging/ChatMember.hpp"
#include "../src/models/messaging/Attachment.hpp"
#include "../src/models/messaging/Notification.hpp"
#include "../src/models/messaging/NotificationSettings.hpp"
#include "../src/models/messaging/VoiceMessage.hpp"

// Groups
#include "../src/models/groups/Group.hpp"
#include "../src/models/groups/GroupMember.hpp"
#include "../src/models/groups/GroupPost.hpp"
#include "../src/models/groups/Page.hpp"
#include "../src/models/groups/PageAdmin.hpp"
#include "../src/models/groups/Event.hpp"
#include "../src/models/groups/EventAttendee.hpp"
#include "../src/models/groups/Poll.hpp"

// Security
#include "../src/models/security/Settings.hpp"
#include "../src/models/security/PrivacySettings.hpp"
#include "../src/models/security/Session.hpp"
#include "../src/models/security/LoginHistory.hpp"
#include "../src/models/security/TwoFactorAuth.hpp"
#include "../src/models/security/Report.hpp"

// Analytics
#include "../src/models/analytics/ProfileStats.hpp"
#include "../src/models/analytics/PostStats.hpp"
#include "../src/models/analytics/ActivityLog.hpp"
#include "../src/models/analytics/SearchHistory.hpp"
#include "../src/models/analytics/ContentRecommendation.hpp"
#include "../src/models/analytics/TrendingTopic.hpp"

// Monetization
#include "../src/models/monetization/Advertisement.hpp"
#include "../src/models/monetization/Wallet.hpp"

// Main function
int main() {
    return doctest::Context::getInstance().run();
}

// ==================== EXCEPTION TESTS ====================

TEST_CASE("SocialNetworkException") {
    SocialNetworkException ex("Test error");
    CHECK(std::string(ex.what()) == "Test error");
}

TEST_CASE("UserNotFoundException") {
    UserNotFoundException ex("user123");
    CHECK(std::string(ex.what()).find("user123") != std::string::npos);
}

TEST_CASE("InvalidCredentialsException") {
    InvalidCredentialsException ex;
    CHECK(std::string(ex.what()).find("Invalid") != std::string::npos);
}

TEST_CASE("DuplicateEmailException") {
    DuplicateEmailException ex("test@test.com");
    CHECK(std::string(ex.what()).find("test@test.com") != std::string::npos);
}

TEST_CASE("PostNotFoundException") {
    PostNotFoundException ex("post123");
    CHECK(std::string(ex.what()).find("post123") != std::string::npos);
}

TEST_CASE("AccessDeniedException") {
    AccessDeniedException ex("No permission");
    CHECK(std::string(ex.what()).find("No permission") != std::string::npos);
}

TEST_CASE("MessageNotFoundException") {
    MessageNotFoundException ex("msg123");
    CHECK(std::string(ex.what()).find("msg123") != std::string::npos);
}

TEST_CASE("InvalidContentException") {
    InvalidContentException ex("Empty content");
    CHECK(std::string(ex.what()).find("Empty content") != std::string::npos);
}

TEST_CASE("GroupNotFoundException") {
    GroupNotFoundException ex("group123");
    CHECK(std::string(ex.what()).find("group123") != std::string::npos);
}

TEST_CASE("AlreadyFriendsException") {
    AlreadyFriendsException ex;
    CHECK(std::string(ex.what()).find("already") != std::string::npos);
}

TEST_CASE("BlockedUserException") {
    BlockedUserException ex("user123");
    CHECK(std::string(ex.what()).find("blocked") != std::string::npos);
}

TEST_CASE("InsufficientBalanceException") {
    InsufficientBalanceException ex(100.0, 50.0);
    CHECK(std::string(ex.what()).find("Insufficient") != std::string::npos);
}

// ==================== USER TESTS ====================

TEST_CASE("User creation and getters") {
    User user("1", "testuser", "test@example.com", "hash123");
    CHECK(user.getId() == "1");
    CHECK(user.getUsername() == "testuser");
    CHECK(user.getEmail() == "test@example.com");
    CHECK(user.isOnline() == false);
}

TEST_CASE("User authentication") {
    User user("1", "testuser", "test@example.com", "hash123");
    CHECK(user.authenticate("hash123") == true);
    CHECK(user.isOnline() == true);
    
    user.logout();
    CHECK(user.isOnline() == false);
}

TEST_CASE("User authentication failure") {
    User user("1", "testuser", "test@example.com", "hash123");
    CHECK_THROWS_AS(user.authenticate("wronghash"), InvalidCredentialsException);
}

TEST_CASE("User update email") {
    User user("1", "testuser", "test@example.com", "hash123");
    user.updateEmail("new@example.com");
    CHECK(user.getEmail() == "new@example.com");
}

// ==================== PROFILE TESTS ====================

TEST_CASE("Profile creation and getters") {
    Profile profile("1", "Ivan", "Petrov");
    CHECK(profile.getUserId() == "1");
    CHECK(profile.getFirstName() == "Ivan");
    CHECK(profile.getLastName() == "Petrov");
    CHECK(profile.getFullName() == "Ivan Petrov");
}

TEST_CASE("Profile update bio") {
    Profile profile("1", "Ivan", "Petrov");
    profile.updateBio("Test bio");
    CHECK(profile.getBio() == "Test bio");
}

TEST_CASE("Profile update avatar") {
    Profile profile("1", "Ivan", "Petrov");
    profile.updateAvatar("http://example.com/avatar.jpg");
    CHECK(profile.getAvatarUrl() == "http://example.com/avatar.jpg");
}

// ==================== FRIENDLIST TESTS ====================

TEST_CASE("FriendList add and remove friends") {
    FriendList friendList("1");
    friendList.addFriend("2");
    CHECK(friendList.isFriend("2") == true);
    CHECK(friendList.getFriendsCount() == 1);
    
    friendList.removeFriend("2");
    CHECK(friendList.isFriend("2") == false);
}

TEST_CASE("FriendList already friends exception") {
    FriendList friendList("1");
    friendList.addFriend("2");
    CHECK_THROWS_AS(friendList.addFriend("2"), AlreadyFriendsException);
}

TEST_CASE("FriendList pending requests") {
    FriendList friendList("1");
    friendList.addPendingRequest("2");
    CHECK(friendList.hasPendingRequest("2") == true);
    
    friendList.acceptRequest("2");
    CHECK(friendList.hasPendingRequest("2") == false);
    CHECK(friendList.isFriend("2") == true);
}

// ==================== FRIENDREQUEST TESTS ====================

TEST_CASE("FriendRequest creation and status") {
    FriendRequest request("1", "2");
    CHECK(request.getSenderId() == "1");
    CHECK(request.getReceiverId() == "2");
    CHECK(request.isPending() == true);
}

TEST_CASE("FriendRequest accept") {
    FriendRequest request("1", "2");
    request.accept();
    CHECK(request.getStatus() == FriendRequestStatus::ACCEPTED);
}

TEST_CASE("FriendRequest reject") {
    FriendRequest request("1", "2");
    request.reject();
    CHECK(request.getStatus() == FriendRequestStatus::REJECTED);
}

// ==================== FOLLOWER TESTS ====================

TEST_CASE("Follower creation") {
    Follower follower("1", "2");
    CHECK(follower.getFollowerId() == "1");
    CHECK(follower.getFolloweeId() == "2");
    CHECK(follower.isActive() == true);
}

TEST_CASE("Follower unfollow") {
    Follower follower("1", "2");
    follower.unfollow();
    CHECK(follower.isActive() == false);
}

// ==================== BLOCKEDUSER TESTS ====================

TEST_CASE("BlockedUser creation") {
    BlockedUser blocked("1", "2", "Spam");
    CHECK(blocked.getBlockerId() == "1");
    CHECK(blocked.getBlockedId() == "2");
    CHECK(blocked.getReason() == "Spam");
    CHECK(blocked.isUserBlocked() == true);
}

TEST_CASE("BlockedUser unblock") {
    BlockedUser blocked("1", "2");
    blocked.unblock();
    CHECK(blocked.isUserBlocked() == false);
}

// ==================== USERSTATUS TESTS ====================

TEST_CASE("UserStatus creation") {
    UserStatus status("1");
    CHECK(status.hasStatus() == false);
}

TEST_CASE("UserStatus update") {
    UserStatus status("1");
    status.updateStatus("Working", "💻", 4);
    CHECK(status.getStatusText() == "Working");
    CHECK(status.getEmoji() == "💻");
    CHECK(status.hasStatus() == true);
}

TEST_CASE("UserStatus clear") {
    UserStatus status("1");
    status.updateStatus("Working", "💻");
    status.clearStatus();
    CHECK(status.hasStatus() == false);
}

// ==================== LOCATION TESTS ====================

TEST_CASE("Location creation") {
    Location loc(55.7558, 37.6173, "Moscow", "Russia");
    CHECK(loc.getLatitude() == 55.7558);
    CHECK(loc.getLongitude() == 37.6173);
    CHECK(loc.getCity() == "Moscow");
    CHECK(loc.getCountry() == "Russia");
}

TEST_CASE("Location format address") {
    Location loc(55.7558, 37.6173, "Moscow", "Russia");
    CHECK(loc.formatAddress() == "Moscow, Russia");
}

TEST_CASE("Location distance calculation") {
    Location moscow(55.7558, 37.6173, "Moscow", "Russia");
    Location spb(59.9343, 30.3351, "Saint Petersburg", "Russia");
    double distance = moscow.getDistance(spb);
    CHECK(distance > 600);
    CHECK(distance < 700);
}

// ==================== POST TESTS ====================

TEST_CASE("Post creation") {
    Post post("1", "user1", "Hello World!");
    CHECK(post.getId() == "1");
    CHECK(post.getAuthorId() == "user1");
    CHECK(post.getContent() == "Hello World!");
    CHECK(post.isPublic() == true);
    CHECK(post.isDeleted() == false);
}

TEST_CASE("Post edit") {
    Post post("1", "user1", "Hello World!");
    post.edit("Updated content");
    CHECK(post.getContent() == "Updated content");
}

TEST_CASE("Post edit empty throws") {
    Post post("1", "user1", "Hello World!");
    CHECK_THROWS_AS(post.edit(""), InvalidContentException);
}

TEST_CASE("Post delete") {
    Post post("1", "user1", "Hello World!");
    post.deletePost();
    CHECK(post.isDeleted() == true);
}

// ==================== COMMENT TESTS ====================

TEST_CASE("Comment creation") {
    Comment comment("1", "post1", "user1", "Nice post!");
    CHECK(comment.getId() == "1");
    CHECK(comment.getPostId() == "post1");
    CHECK(comment.getText() == "Nice post!");
    CHECK(comment.isReply() == false);
}

TEST_CASE("Comment reply") {
    Comment comment("2", "post1", "user2", "Thanks!", "1");
    CHECK(comment.isReply() == true);
    CHECK(comment.getParentId() == "1");
}

TEST_CASE("Comment edit") {
    Comment comment("1", "post1", "user1", "Nice post!");
    comment.edit("Edited comment");
    CHECK(comment.getText() == "Edited comment");
    CHECK(comment.isEdited() == true);
}

// ==================== LIKE TESTS ====================

TEST_CASE("Like creation") {
    Like like("1", "user1", "post1", LikeTargetType::POST);
    CHECK(like.getUserId() == "user1");
    CHECK(like.getTargetId() == "post1");
    CHECK(like.getTargetType() == LikeTargetType::POST);
}

TEST_CASE("Like matches target") {
    Like like("1", "user1", "post1", LikeTargetType::POST);
    CHECK(like.matchesTarget("post1", LikeTargetType::POST) == true);
    CHECK(like.matchesTarget("post2", LikeTargetType::POST) == false);
}

// ==================== SHARE TESTS ====================

TEST_CASE("Share creation") {
    Share share("1", "user1", "post1", "Check this out!");
    CHECK(share.getUserId() == "user1");
    CHECK(share.getPostId() == "post1");
    CHECK(share.getMessage() == "Check this out!");
    CHECK(share.hasMessage() == true);
}

// ==================== STORY TESTS ====================

TEST_CASE("Story creation") {
    Story story("1", "user1", "http://example.com/story.jpg");
    CHECK(story.getAuthorId() == "user1");
    CHECK(story.getViewCount() == 0);
    CHECK(story.isActive() == true);
}

TEST_CASE("Story view") {
    Story story("1", "user1", "http://example.com/story.jpg");
    story.view();
    story.view();
    CHECK(story.getViewCount() == 2);
}

// ==================== ALBUM TESTS ====================

TEST_CASE("Album creation") {
    Album album("1", "user1", "Vacation", "Summer 2024");
    CHECK(album.getName() == "Vacation");
    CHECK(album.getDescription() == "Summer 2024");
    CHECK(album.getPhotoCount() == 0);
}

TEST_CASE("Album add photo") {
    Album album("1", "user1", "Vacation");
    album.addPhoto("photo1");
    album.addPhoto("photo2");
    CHECK(album.getPhotoCount() == 2);
}

// ==================== VIDEO TESTS ====================

TEST_CASE("Video creation") {
    Video video("1", "user1", "http://example.com/video.mp4", "My Video", 120);
    CHECK(video.getTitle() == "My Video");
    CHECK(video.getDuration() == 120);
    CHECK(video.getDurationFormatted() == "2:00");
}

TEST_CASE("Video play increments views") {
    Video video("1", "user1", "http://example.com/video.mp4", "My Video", 120);
    video.play();
    video.play();
    CHECK(video.getViews() == 2);
}

// ==================== TAG TESTS ====================

TEST_CASE("Tag creation normalizes name") {
    Tag tag("1", "#Programming");
    CHECK(tag.getName() == "programming");
    CHECK(tag.getHashtag() == "#programming");
}

TEST_CASE("Tag usage count") {
    Tag tag("1", "cpp");
    tag.incrementUsage();
    tag.incrementUsage();
    CHECK(tag.getUsageCount() == 2);
}

// ==================== REACTION TESTS ====================

TEST_CASE("Reaction creation") {
    Reaction reaction("1", "user1", "post1", ReactionType::LOVE);
    CHECK(reaction.getTypeString() == "love");
    CHECK(reaction.getEmoji() == "❤️");
}

TEST_CASE("Reaction change type") {
    Reaction reaction("1", "user1", "post1", ReactionType::LIKE);
    reaction.changeType(ReactionType::HAHA);
    CHECK(reaction.getTypeString() == "haha");
}

// ==================== MESSAGE TESTS ====================

TEST_CASE("Message creation") {
    Message msg("1", "user1", "user2", "Hello!");
    CHECK(msg.getContent() == "Hello!");
    CHECK(msg.isRead() == false);
}

TEST_CASE("Message mark as read") {
    Message msg("1", "user1", "user2", "Hello!");
    msg.markAsRead();
    CHECK(msg.isRead() == true);
}

// ==================== CHAT TESTS ====================

TEST_CASE("Chat creation") {
    std::vector<std::string> participants = {"user1", "user2"};
    Chat chat("1", participants);
    CHECK(chat.hasParticipant("user1") == true);
    CHECK(chat.getParticipantCount() == 2);
}

// ==================== GROUPCHAT TESTS ====================

TEST_CASE("GroupChat creation") {
    GroupChat gc("1", "Friends", "admin1");
    CHECK(gc.getName() == "Friends");
    CHECK(gc.isAdmin("admin1") == true);
    CHECK(gc.getMemberCount() == 1);
}

TEST_CASE("GroupChat add member") {
    GroupChat gc("1", "Friends", "admin1");
    gc.addMember("user2");
    CHECK(gc.getMemberCount() == 2);
    CHECK(gc.isMember("user2") == true);
}

// ==================== NOTIFICATION TESTS ====================

TEST_CASE("Notification creation") {
    Notification n("1", "user1", NotificationType::LIKE, "Someone liked your post");
    CHECK(n.getMessage() == "Someone liked your post");
    CHECK(n.isRead() == false);
}

TEST_CASE("Notification mark as read") {
    Notification n("1", "user1", NotificationType::LIKE, "Someone liked your post");
    n.markAsRead();
    CHECK(n.isRead() == true);
}

// ==================== GROUP TESTS ====================

TEST_CASE("Group creation") {
    Group group("1", "Developers", "owner1");
    CHECK(group.getName() == "Developers");
    CHECK(group.isOwner("owner1") == true);
    CHECK(group.getMemberCount() == 1);
}

TEST_CASE("Group add member") {
    Group group("1", "Developers", "owner1");
    group.addMember("user2");
    CHECK(group.isMember("user2") == true);
}

// ==================== PAGE TESTS ====================

TEST_CASE("Page creation") {
    Page page("1", "TechNews", "Technology", "owner1");
    CHECK(page.getName() == "TechNews");
    CHECK(page.getCategory() == "Technology");
    CHECK(page.getFollowersCount() == 0);
}

TEST_CASE("Page increment followers") {
    Page page("1", "TechNews", "Technology", "owner1");
    page.incrementFollowers();
    page.incrementFollowers();
    CHECK(page.getFollowersCount() == 2);
}

// ==================== POLL TESTS ====================

TEST_CASE("Poll creation") {
    std::vector<std::string> options = {"Yes", "No", "Maybe"};
    Poll poll("1", "Do you like C++?", options, "user1");
    CHECK(poll.getQuestion() == "Do you like C++?");
    CHECK(poll.getOptions().size() == 3);
}

TEST_CASE("Poll vote") {
    std::vector<std::string> options = {"Yes", "No"};
    Poll poll("1", "Question?", options, "user1");
    poll.vote(0);
    poll.vote(0);
    poll.vote(1);
    CHECK(poll.getVotesForOption(0) == 2);
    CHECK(poll.getVotesForOption(1) == 1);
    CHECK(poll.getTotalVotes() == 3);
}

// ==================== SETTINGS TESTS ====================

TEST_CASE("Settings creation") {
    Settings settings("user1");
    CHECK(settings.getTheme() == Theme::SYSTEM);
    CHECK(settings.getLanguage() == "ru");
}

TEST_CASE("Settings change theme") {
    Settings settings("user1");
    settings.setTheme(Theme::DARK);
    CHECK(settings.getThemeString() == "dark");
}

// ==================== PRIVACYSETTINGS TESTS ====================

TEST_CASE("PrivacySettings make private") {
    PrivacySettings privacy("user1");
    privacy.makePrivate();
    CHECK(privacy.getProfileVisibility() == ProfileVisibility::PRIVATE);
    CHECK(privacy.isSearchable() == false);
}

// ==================== SESSION TESTS ====================

TEST_CASE("Session creation") {
    Session session("1", "user1", "token123", "192.168.1.1", "Chrome/100");
    CHECK(session.getToken() == "token123");
    CHECK(session.isActive() == true);
}

TEST_CASE("Session terminate") {
    Session session("1", "user1", "token123", "192.168.1.1", "Chrome/100");
    session.terminate();
    CHECK(session.isActive() == false);
    CHECK(session.isValid() == false);
}

// ==================== WALLET TESTS ====================

TEST_CASE("Wallet deposit") {
    Wallet wallet("user1");
    wallet.deposit(100.0);
    CHECK(wallet.getBalance() == 100.0);
}

TEST_CASE("Wallet withdraw") {
    Wallet wallet("user1");
    wallet.deposit(100.0);
    wallet.withdraw(30.0);
    CHECK(wallet.getBalance() == 70.0);
}

TEST_CASE("Wallet insufficient balance") {
    Wallet wallet("user1");
    wallet.deposit(50.0);
    CHECK_THROWS_AS(wallet.withdraw(100.0), InsufficientBalanceException);
}

TEST_CASE("Wallet transfer") {
    Wallet wallet1("user1");
    Wallet wallet2("user2");
    wallet1.deposit(100.0);
    wallet1.transfer(wallet2, 40.0);
    CHECK(wallet1.getBalance() == 60.0);
    CHECK(wallet2.getBalance() == 40.0);
}

// ==================== PROFILESTATS TESTS ====================

TEST_CASE("ProfileStats engagement rate") {
    ProfileStats stats("user1");
    stats.updateStats(10, 100, 50);
    stats.incrementLikes();
    stats.incrementLikes();
    stats.incrementComments();
    CHECK(stats.getFollowerRatio() == 2.0);
}

// ==================== POSTSTATS TESTS ====================

TEST_CASE("PostStats engagement") {
    PostStats stats("post1");
    stats.incrementLikes();
    stats.incrementComments();
    stats.incrementViews();
    stats.incrementViews();
    CHECK(stats.getTotalEngagement() == 2);
}

// ==================== ADVERTISEMENT TESTS ====================

TEST_CASE("Advertisement creation") {
    Advertisement ad("1", "advertiser1", "Buy now!", 1000.0);
    CHECK(ad.getBudget() == 1000.0);
    CHECK(ad.isActive() == false);
}

TEST_CASE("Advertisement activate and display") {
    Advertisement ad("1", "advertiser1", "Buy now!", 1000.0);
    ad.activate();
    ad.display();
    CHECK(ad.getImpressions() == 1);
}

TEST_CASE("Advertisement click through rate") {
    Advertisement ad("1", "advertiser1", "Buy now!", 1000.0);
    ad.activate();
    ad.display();
    ad.display();
    ad.trackClick(0.5);
    CHECK(ad.getClickThroughRate() == 50.0);
}
