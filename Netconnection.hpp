#pragma once
/**
 * Author: Simon Brisebois-Therrien
 * Date: 2021-08-08
 * Documentation: 
 *  - https://www.adobe.com/content/dam/acom/en/devnet/rtmp/pdf/rtmp_specification_1.0.pdf
 *  (Page 29-33)
 **/

#include <string>
#include <map>

#include "../utils/Object.hpp"

using namespace std;




class Netconnection
{
    public:
        enum class CommandType
        {
            Null,
            Connect,
            ConnectResponse,
            Call,
            CallResponse,
            CreateStream,
            CreateStreamResponse,
            OnStatus,
            Play,
            Play2,
            DeleteStream,
            ReceiveAudio,
            ReceiveVideo,
            Publish,
            Seek,
            Pause,
            ReleaseStream,
            FCPublish
        }; 
        
        static inline map<std::string, CommandType> CommandLinker = {
            {"connect", CommandType::Connect},
            {"connectResponse", CommandType::ConnectResponse},
            {"call", CommandType::Call},
            {"callResponse", CommandType::CallResponse},
            {"createStream", CommandType::CreateStream},
            {"createStreamResponse", CommandType::CreateStreamResponse},
            {"onStatus", CommandType::OnStatus},
            {"play", CommandType::Play},
            {"play2", CommandType::Play2},
            {"deleteStream", CommandType::DeleteStream},
            {"receiveAudio", CommandType::ReceiveAudio},
            {"receiveVideo", CommandType::ReceiveVideo},
            {"publish", CommandType::Publish},
            {"seek", CommandType::Seek},
            {"pause", CommandType::Pause},
            {"releaseStream", CommandType::ReleaseStream},
            {"FCPublish", CommandType::FCPublish}
        };


        struct Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::Null;
            /**
             * Command Name
             * 
             * Name of the command.
             **/
            std::string CommandName;
            
            /**
             * Transaction ID
             **/
            unsigned short TransactionID;

            /**
             * Command Utils::Object
             * 
             * Command information Utils::Object which has name-value pairs.
             **/
            Utils::Object CommandObject;

            virtual ~Command() = default;
        };

        struct Connect : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::Connect;

            /**
             * Command Name
             * 
             * Name of the command. Set to 'connect'.
             **/
            std::string CommandName = "connect";

            /**
             * Always set to 1.
             **/
            unsigned short TransactionID = 1;

            /**
             * Any optional arguments to be provided.
             **/
            Utils::Object OptionalUserArguments;
        };

        struct ConnectResponse : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::ConnectResponse;

            /**
             * Command Name
             * 
             * _result or _error; indicates whether the response is result or error.
             **/
            std::string CommandName;

            /**
             * Transaction ID
             * 
             * Transaction ID is 1 for connect responses.
             **/
            unsigned short TransactionID = 1;

            /**
             * Properties
             * 
             * Name-value pairs that describe the properties of the connection.
             **/
            Utils::Object Properties;

            /**
             * Information
             * 
             * Name-value pairs that describe the response from|the server.
             * 'code', 'level' or 'description' are name of few among such
             * information.
             **/
            Utils::Object Information;
        };

        struct Call : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::Call;
            
            /**
             * Procedure Name
             * 
             * Name of the remote procedure that is called.
             **/
            std::string CommandName;
            
            /**
             * Transaction ID
             * 
             * If a response is expected, we give a transaction ID.
             * Else, we pass the value of 0.
             **/
            unsigned short TransactionID;

            /**
             * Any optional arguments to be provided.
             **/
            Utils::Object OptionalArguments;
        };

        struct CallResponse : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::CallResponse;
            
            /**
             * Transaction ID
             * 
             * ID of the command, to which the response belongs.
             **/
            unsigned short TransactionID;

            /**
             * Command Utils::Object
             * 
             * If there exists any command info, this is set.
             * Else, this is set to null type.
             **/
            Utils::Object CommandObject;
            
            /**
             * Response
             * 
             * Response from the method called.
             **/
            Utils::Object Response;
        };

        struct CreateStream : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::CreateStream;

            /**
             * Command Name
             **/   
            std::string CommandName = "createStream";

            /**
             * Transaction ID
             * 
             * Transaction ID of the command.
             **/
            unsigned short TransactionID;
        };

        struct CreateStreamResponse : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::CreateStreamResponse;

            /**
             * Command Name
             * 
             * _result or _error; indicates whether the response is result or error.
             **/
            std::string CommandName;
            
            /**
             * Stream ID
             * 
             * The return value is either a stream ID or an error information Utils::Object.
             **/
            unsigned int StreamID;
        };

        struct OnStatus : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::OnStatus;
            
            /**
             * Command Name
             **/
            std::string CommandName;

            /**
             * Transaction ID
             **/
            unsigned short TransactionID = 0;

            /**
             * Command Utils::Object
             * 
             * There is no command Utils::Object for onStatus messages.
             **/
            Utils::Object CommandObject;

            /**
             * Information Utils::Object.
             **/
            Utils::Object Information;
        };

        struct Play : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::Play;

            /**
             * Command Name
             **/
            std::string CommandName = "play";

            /**
             * Transaction ID
             **/
            unsigned short TransactionID = 0;
            
            /**
             * Command Utils::Object
             * 
             * Command information does not exist. Set to null type.
             **/
            Utils::Object CommandObject;

            /**
             * Stream Name
             * 
             * Name of the stream to play.
             * To play video (FLV) files, specify the name of the stream without 
             * extension (for example, "sample"). To play back MP3 or ID3 tags,
             * you must precede the stream name with mp3: (for example, "mp3:sample".
             * To play H.264/AAC files, you must precede the stream name with mp4:
             * and specify the file extension. For example: "mp4:sample.m4v").
             **/
            std::string StreamName;

            /**
             * Start
             * 
             * An optional parameter that specifies the start time in seconds. The default
             * value is -2, which means the subscriber first tries to play the live stream
             * specified in the stream name field.
             **/
            int Start = -2;

            /**
             * Duration
             * 
             * An optional parameter that specifies the duration of playback in seconds. 
             * The default value is -1. The -1 value means a live stream is played until
             * it ends. 
             **/
            int duration = -1;

            /**
             * Reset
             * 
             * An optional Boolean value or number that specifies whether to flush any
             * previous playlist.
             **/
            bool Reset = 0;
        };

        struct Play2 : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::Play2;

            /**
             * Command Name
             **/
            std::string CommandName = "play2";

            /**
             * Transaction ID
             **/
            unsigned short TransactionID = 0;
            
            /**
             * Command Utils::Object
             * 
             * Command information does not exist. Set to null type.
             **/
            Utils::Object CommandObject;

            /**
             * Parameters
             * 
             * An AMF encoded Utils::Object whose properties are the public properties described
             * for the flash.net.NetStreamPlayOptions ActionScript Utils::Object.
             **/
            Utils::Object Parameters;
        };

        struct DeleteStream : public Command
        {
            /**
             * Command type.
             **/
            CommandType type = CommandType::DeleteStream;

            /**
             * Command Name
             **/
            std::string commandName = "deleteStream";

            /**
             * Transaction ID
             **/
            unsigned short TransactionID = 0;

            /**
             * Stream ID
             **/
            int StreamID = 0;
        };

        struct ReceiveAudio : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::ReceiveAudio;

            /**
             * Command Name
             **/
            std::string CommandName = "receiveAudio";

            /**
             * Transaction ID
             **/
            unsigned short TransactionID = 0;

            /**
             * Command Utils::Object
             * 
             * Command information Utils::Object does not exist. Set to null type.
             **/
            Utils::Object CommandObject;

            /**
             * Bool Flag
             * 
             * True or false to indicate whether to receive audio or not.
             **/
            bool BoolFlag = 0;
        };

        struct ReceiveVideo : public Command
        {   
            /**
             * Command Type
             **/
            CommandType type = CommandType::ReceiveVideo;

            /**
             * Command Name
             **/
            std::string CommandName = "receiveVideo";

            /**
             * Transaction ID
             **/
            unsigned short TransactionID = 0;
            
            /**
             * Command Utils::Object
             * 
             * Command information Utils::Object does not exist. Set to null type.
             **/
            Utils::Object CommandObject;

            /**
             * Bool Flag
             * 
             * True or false to indicate whether to receive video or not.
             **/
            bool BoolFlag = 0;
        };

        struct Publish : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::Publish;
            
            /**
             * Command Name
             **/
            std::string CommandName = "publish";

            /**
             * Transaction ID is set to 0.
             **/
            unsigned short TransactionID = 0;

            /**
             * Command Utils::Object
             * 
             * Command information Utils::Object does not exist. Set to null type.
             **/
            Utils::Object CommandObject;

            /**
             * Publishing Name
             * 
             * Name with which the stream is published.
             **/
            std::string PublishingName;

            /**
             * Publishing Type
             * 
             * Type of publishing. Set to "live", "record" or "append".
             * 
             * Record: The stream is published and the data is stored on the server
             * in a subdirectory within the directory that contains the server application.
             * If the file already exists, it is overriden.
             * 
             * Append: The stream is published and the data is appended to a file. If no
             * file is found, it is created.
             * 
             * Live: Live data is published without recording it in a file.
             **/
            std::string PublishingType;
        };  

        struct Seek : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::Seek;

            /**
             * Command Name
             **/
            std::string CommandName = "seek"; 
            
            /**
             * Transaction ID
             * 
             * Transaction ID is set to 0.
             **/
            unsigned short TransactionID = 0;

            /**
             * Command Utils::Object
             * 
             * There is no command information Utils::Object for this command. Set to null type.
             **/
            Utils::Object CommandObject;

            /**
             * Milliseconds
             * 
             * Number of milliseconds to seek into the playlist.
             **/
            int milliseconds = 0;
        };

        struct Pause : public Command
        {
            /**
             * Command Type
             **/
            CommandType type = CommandType::Pause;

            /**
             * Command Name
             **/
            std::string CommandName = "pause";
            
            /**
             * Transaction ID
             * 
             * Transaction ID is set to 0.
             **/
            unsigned short TransactionID = 0;

            /**
             * Command Utils::Object
             * 
             * Command information Utils::Object does not exist. Set to null type.
             **/
            Utils::Object CommandObject;

            /**
             * Pause/Unpause Flag
             * 
             * True or false, to indicate pausing or resuming play.
             **/
            bool pause = false;

            /**
             * Milliseconds
             * 
             * Number of milliseconds at which the stream is paused or play resumed.
             * This is the current stream time at the Client when stream was paused.
             * When the playback is resumed, the server will only send messages with
             * timestamps greater than this value.
             **/
            int Milliseconds = 0;
        };        

        struct ReleaseStream : public Command
        {
            CommandType type = CommandType::ReleaseStream;

            std::string CommandName = "releaseStream";

            unsigned short TransactionID = 0;

            std::string StreamName;
        };

        struct FCPublish : public Command
        {
            CommandType type = CommandType::FCPublish;
            std::string CommandName = "FCPublish";

            unsigned short TransactionID = 0;

            std::string StreamName;
        };

    public:
        
        /**
         * Connect command:
         * 
         * 1- Client sends the connect command to the server to
         *    request to connect with the server application instance.
         * 2- After receiving the connect command, the server sends
         *    the protocol message 'Window Acknowledgement Size' to 
         *    the client. The server also connects the client to the app.
         * 3- The server sends the protocol message 'Set Peer Bandwidth'
         *    to the client.
         * 4- The client sends the protocol message 'Window Ack. Size'
         *    to the server after processing the protocol message
         *    'Set Peer Bandwidth'.
         * 5- The server sends another protocol message of type
         *    User Control Message(StreamBegin) to the client.
         * 6- The server sends the result command message informing the
         *    client of the connection status (success/fail). The command
         *    specifies the transaction ID (always equal to 1 for the connect
         *    command). The message also specifies the properties, such as
         *    Flash Media Server version (string). In addition, it specifies
         *    other connection response related infromations like level (string),
         *    code (string), description (string), Utils::ObjectEncoding (number)...
         **/
        void connect();
        /**
         * The call method runs remote procedure call (RPC) at the
         * receiving end.
         **/
        void call(std::string RPCName);
        void close();
        /**
         * The client sends this command to the server to create a
         * logical channel for message communication. The publishing
         * of audio, video and metadata is carried out over stream
         * channel created using the createStream command.
         * 
         * NetConnection is the default communication channel, which
         * has a stream ID of 0. Protocol and a few command messages,
         * including createStream, use the default communication channel.
         **/
        void createStream();

        enum AudioCodecs
        {
            /**
             * Raw sound, no compression.
             **/
            SUPPORT_SND_NONE = 0x0001,
            /**
             * ADPCM compression.
             **/
            SUPPORT_SND_ADPCM = 0x0002,
            /**
             * MP3 compression.
             **/
            SUPPORT_SND_MP3 = 0x0004,
            /**
             * Not used.
             **/
            SUPPORT_SND_INTEL = 0x0008,
            /**
             * Not used.
             **/
            SUPPORT_SND_UNUSED = 0x0010,
            /**
             * NellyMoser at 8 kHz compression.
             **/
            SUPPORT_SND_NELLY8 = 0x0020,
            /**
             * NellyMoser compression (5, 11, 22 and 44 kHz).
             **/
            SUPPORT_SND_NELLY = 0x0040,
            /**
             * G711A sound compression (Flash Media Server only).
             **/
            SUPPORT_SND_G711A = 0x0080,
            /**
             * G711U sound compression (Flash Media Server only).
             **/
            SUPPORT_SND_G711U = 0x0100,
            /**
             * NellyMouser at 16 kHz compression.
             **/
            SUPPORT_SND_NELLY16 = 0x0200,
            /**
             * Advanced audio coding (AAC) codec.
             **/
            SUPPORT_SND_AAC = 0x0400,
            /**
             * Speex audio
             **/
            SUPPORT_SND_SPEEX = 0x0800,
            /**
             * All RTMP-supported audio codecs.
             **/
            SUPPORT_SND_ALL = 0x0FFF
        };

        enum VideoCodecs
        {
            /**
             * Obsolete value.
             **/
            SUPPORT_VID_UNUSED = 0x0001,
            /**
             * Obsolete value.
             **/
            SUPPORT_VID_JPEG = 0x0002,
            /**
             * Sorenson Flash video.
             **/
            SUPPORT_VID_SORENSON = 0x0004,
            /**
             * V1 screen sharing.
             **/
            SUPPORT_VID_HOMEBREW = 0x0008,
            /**
             * On2 video (Flash 8+).
             **/
            SUPPORT_VID_VP6 = 0x0010,
            /**
             * On2 video with alpha channel.
             **/
            SUPPORT_VID_VP6ALPHA = 0x0020,
            /**
             * Screen sharing version 2 (Flash 8+).
             **/
            SUPPORT_VID_HOMEBREWV = 0x0040,
            /**
             * H264 video.
             **/
            SUPPORT_VID_H264 = 0x0080,
            /**
             * All RTMP-supported video codecs.
             **/
            SUPPORT_VID_ALL = 0x00FF
        };

        enum VideoFunction 
        {
            /**
             * Indicates that the client can perform frame-accurate seeks.
             **/
            SUPPORT_VID_CLIENT_SEEK = 1
        };

        enum ObjectEncoding
        {
            AMF0 = 0,
            AMF3 = 3
        };
};