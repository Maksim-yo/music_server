#ifndef CONSTANTS_H
#define CONSTANTS_H


enum Owner{

    Client,
    Server
};
enum MessageType{

    ArtistMessage,
    TrackMessage,
    PlayListMessage,
    SettingsMessage,
    RegistrationMessage,
    AuthorizationMessage,
    ServerDeny,
    ServerAccept,
    PingMessage,
    PongMessage


};


#endif // CONSTANTS_H
