//
//  AferoSofthub.h
//  iTokui
//
//  Created by Justin Middleton on 11/18/15.
//  Copyright © 2015 Kiban Labs, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma mark - AferoSofthub state constants

static NSString * _Nonnull const AferoSofthubDomain = @"AferoSofthub";

typedef NS_ENUM(NSInteger, AferoSofthubError) {
    AferoSofthubErrorConclaveAccessEncoding = -1,
    AferoSofthubErrorInvalidRSSIDecibelValue = -2,
    AferoSofthubErrorInvalidStateForCmd = -3,
};

/*! Sent when the in-progress OTA count changes to a nonzero number */
static NSString * _Nonnull const AferoSofthubOTAInProgressNotification = @"AferoSofthubOTAInProgressNotification";

/*! The number of AferoSofthub OTAs in progress */
static NSString * _Nonnull const AferoSofthubOTACountKey = @"AferoSofthubOTACountKey";

/*! Sent when the in-progress OTA count changes to zero */
static NSString * _Nonnull const AferoSofthubOTACompleteNotification = @"AferoSofthubOTACompleteNotification";

#pragma mark - AferoSofthub main

/*!
 A wrapper for the AferoSofthub service.
 */
@interface AferoSofthub : NSObject

/**
 @typedef State of the AferoSofthub service
 @constant AferoSofthubStateStopping The softhub is in the process of shutting down.
 @constant AferoSofthubStateStopped The softhub is inactive.
 @constant AferoSofthubStateStarting The softhub is starting up.
 @constant AferoSofthubStateStarted The softhub is running.
 */
typedef NS_ENUM(NSInteger, AferoSofthubState) {
    AferoSofthubStateStopping,
    AferoSofthubStateStopped,
    AferoSofthubStateStarting,
    AferoSofthubStateStarted,
};

@property (nonatomic, readonly) AferoSofthubState state;
+ (AferoSofthubState)state;


@property (nonatomic, readonly) NSInteger otaCount;


/**
 @typedef AferoSofthubLogLevel Softhub ASL log level.
 @constant AferoSofthubLogLevelNone No softhub logging.
 @constant AferoSofthubLogLevelError Log softhub errors only.
 @constant AferoSofthubLogLevelWarning Log softhub errors and warnings.
 @constant AferoSofthubLogLevelInfo Log softhub errors, warnings, and general info.
 @constant AferoSofthubLogLevelDebug Log softhub debug messages, in addtion to errors, warning, and info.
 @constant AferoSofthubLogLevelVerbose Make the softhub really chatty.
 @constatn AferoSofthubLogLevelTrace Make the softhub really, really chatty.
 */

typedef NS_ENUM(NSInteger, AferoSofthubLogLevel) {
    AferoSofthubLogLevelNone = 0,
    AferoSofthubLogLevelError,
    AferoSofthubLogLevelWarning,
    AferoSofthubLogLevelInfo,
    AferoSofthubLogLevelDebug,
    AferoSofthubLogLevelVerbose,
    AferoSofthubLogLevelTrace,
};

typedef void (^AferoSofthubSecureHubAssociationHandler)(NSString *_Nonnull assId);

/**
 @typedef AferoSofthubCompleteReason
 @brief   Represents the reason the softhub service stopped.
 @constant AferoSofthubCompleteReasonStopCalled This is the "normal" run return value. @see AferoSofthubCompleteReason
 @constant AferoSofthubCompleteReasonMissingSofthubSetupPath Run was called without the ConfigName::SOFT_HUB_SETUP_PATH config value being set. @see AferoSofthubCompleteReason
 @constant AferoSofthubCompleteReasonUnhandledService Run was called with the ConfigName::SERVICE config value we don't support. @see AferoSofthubCompleteReason
 @constant AferoSofthubCompleteReasonFileIOError We had a file related error loading our config values. @see AferoSofthubCompleteReason
 @constant AferoSofthubSerHubbyCompleteReasonSetupFailedviceSetupFailed The setup process for the embedded softhub has failed. @see AferoSofthubCompleteReason
 */

typedef NS_ENUM(NSInteger, AferoSofthubCompleteReason) {
    AferoSofthubCompleteReasonStopCalled = 0,
    AferoSofthubCompleteReasonMissingSofthubSetupPath,
    AferoSofthubCompleteReasonUnhandledService,
    AferoSofthubCompleteReasonFileIOError,
    AferoSofthubCompleteReasonSetupFailed,
};

typedef void(^AferoSofthubCompleteReasonHandler)(AferoSofthubCompleteReason cr);

typedef NS_ENUM(NSInteger, AferoService) {
    AferoServiceProd = 0,
    AferoServiceDev,
};

/*!
 Run AferoSofthub.
 */

/**
 Start the softhub with the given account id.
 @param accountId The accountId to which the softhub will be associated.
 @param logLevel The LogLevel to use
 @param associationHandler A callback the softhub will invoke if/when it needs
 to associate itself with an account
 @note Using this form of the call passes `nil` as the `hardwareIdentifier`.
 */

+ (void)startWithAccountId:(NSString *_Nonnull)accountId
                  logLevel:(AferoSofthubLogLevel)logLevel
        associationHandler:(AferoSofthubSecureHubAssociationHandler _Nonnull)associationHandler
         completionHandler:(AferoSofthubCompleteReasonHandler _Nonnull)completionHandler;

/*!
 Start the softhub with the given account id.
 @param accountId The accountId to which the softhub will be associated.
 @param logLevel The LogLevel to use
 @param hardwareIdentifier A string to place in the softhub device's hardware info attribute,
                           `id=51101`, `semanticType`="Hubby HW Info"
 @param associationHandler A callback the softhub will invoke if/when it needs
 to associate itself with an account
 */

+ (void)startWithAccountId:(NSString *_Nonnull)accountId
                  logLevel:(AferoSofthubLogLevel)logLevel
        hardwareIdentifier:(NSString *_Nullable)hardwareIdentifier
        associationHandler:(AferoSofthubSecureHubAssociationHandler _Nonnull)associationHandler
         completionHandler:(AferoSofthubCompleteReasonHandler _Nonnull)completionHandler;

/*!
 Start the softhub with the given account id.
 @param accountId The accountId to which the softhub will be associated.
 @param cloud The cloud to use.
 @param logLevel The LogLevel to use
 @param hardwareIdentifier A string to place in the softhub device's hardware info attribute,
 `id=51101`, `semanticType`="Hubby HW Info"
 @param associationHandler A callback the softhub will invoke if/when it needs
 to associate itself with an account
 */

+ (void)startWithAccountId:(NSString *_Nonnull)accountId
                     cloud:(AferoService)cloud
                  logLevel:(AferoSofthubLogLevel)logLevel
        hardwareIdentifier:(NSString *_Nullable)hardwareIdentifier
        associationHandler:(AferoSofthubSecureHubAssociationHandler _Nonnull)associationHandler
         completionHandler:(AferoSofthubCompleteReasonHandler _Nonnull)completionHandler;

/*!
 Stop AferoSofthub.
 */
+ (void)stop;

@end

#pragma mark - WIFI Setup

/**
 Wrapper for SSID entries coming back grom AferoSofthub.
 */
@interface AferoSofthubWifiSSIDEntryWrapper: NSObject

@property (nonatomic, readonly) NSString *_Nonnull SSID;
@property (nonatomic, readonly) NSInteger RSSI;
@property (nonatomic, readonly) NSInteger RSSIBars;
@property (nonatomic, readonly) BOOL isSecure;
@property (nonatomic, readonly) BOOL isConnected;

@end

@interface AferoSofthub (WiFiConfig)

#define WIFI_SETUP_STATE_ATTRIBUTE 65007
#define WIFI_CURRENT_SSID_ATTRIBUTE 65004
#define WIFI_NETWORK_TYPE_ATTRIBUTE 65008
#define WIFI_STEADY_STATE_ATTRIBUTE 65006
#define WIFI_RSSI_ATTRIBUTE 65005

/**
@typedef AferoSofthubWifiAttributeId
@brief Attribute IDs used for wifi setup.
@constant AferoSofthubWifiAttributeIdCurrentSSID The attributeId for the currently-connected wifi SSID.
@constant AferoSofthubWifiAttributeIdNetworkType The attributeId for the current networkType. @see AferoSofthubWifiNetworkType.
@constant AferoSofthubWifiAttributeIdSetupState The attributeId for the current wifi setup state. @see AferoSofthubWifiState.
@constant AferoSofthubWifiAttributeIdSteadyState The attributeId for the current wifi steady state. @see AferoSofthubWifiState.
@constant AferoSofthubWifiAttributeIdRSSI The attributeId for the current RSSI for the connected wifi SSID.
*/

typedef NS_ENUM(NSInteger, AferoSofthubWifiAttributeId) {
    
    /// The attributeId for the currently-connected wifi SSID.
    AferoSofthubWifiAttributeIdCurrentSSID = WIFI_CURRENT_SSID_ATTRIBUTE,
    
    /// The attributeId for the current networkType. @see AferoSofthubWifiNetworkType.
    AferoSofthubWifiAttributeIdNetworkType = WIFI_NETWORK_TYPE_ATTRIBUTE,
    
    /// The attributeId for the current wifi setup state. @see AferoSofthubWifiState.
    AferoSofthubWifiAttributeIdSetupState = WIFI_SETUP_STATE_ATTRIBUTE,
    
    /// The attributeId for the current wifi steady state. @see AferoSofthubWifiState.
    AferoSofthubWifiAttributeIdSteadyState = WIFI_STEADY_STATE_ATTRIBUTE,
    
    /// The attributeId for the current RSSI for the connected wifi SSID.
    AferoSofthubWifiAttributeIdRSSI = WIFI_RSSI_ATTRIBUTE,
};

/**
 @typedef AferoSofthubWifiNetworkType
 @brief Network type currently used by the hub.
 @constant AferoSofthubWifiNetworkTypeEthernet Type for an ethernet network. @see AferoSofthubWifiNetworkType.
 @constant AferoSofthubWifiNetworkTypeWLAN Type for a wifi network. @see AferoSofthubWifiNetworkType.
 @constant AferoSofthubWifiNetworkTypeWAN Type for an WAN (e.g., LTE) network. @see AferoSofthubWifiNetworkType.
 */
typedef NS_ENUM(NSInteger, AferoSofthubWifiNetworkType) {
    AferoSofthubWifiNetworkTypeEthernet = 0,
    AferoSofthubWifiNetworkTypeWLAN     = 1,
    AferoSofthubWifiNetworkTypeWAN      = 2,
};

/*!
 @typedef AferoSofthubWifiState
 @brief The current state of the wifi connection process, used for `WifiSetupStateAttributeId` and `WifiSteadyStateAttributeId`.
 @constant AferoSofthubWifiStateNotConnected The setup process has started
 @constant AferoSofthubWifiStatePending We can see the hub
 @constant AferoSofthubWifiStateConnected We've connected to the hub
 @constant AferoSofthubWifiStateUnknownFailure Setup failed for an unknown reason.
 @constant AferoSofthubWifiStateAssociationFailed We failed associating with the wifi base station (pre-authentication).
 @constant AferoSofthubWifiStateHandshakeFailed We failed attempting to connect to the base station, probably due to an authentication failure.
                                         Retrying with a new password may help.
 @constant AferoSofthubWifiStateEchoFailed We successfully authenticated to the base station, but cannot see the Afero cloud.
 @constant AferoSofthubWifiStateSSIDNotFound The SSID we're trying to connect to is (no longer) visible.
 */

typedef NS_ENUM(NSInteger, AferoSofthubWifiState) {
    AferoSofthubWifiStateNotConnected      = 0,
    AferoSofthubWifiStatePending           = 1,
    AferoSofthubWifiStateConnected         = 2,
    AferoSofthubWifiStateUnknownFailure    = 3,
    AferoSofthubWifiStateAssociationFailed = 4,
    AferoSofthubWifiStateHandshakeFailed   = 5,
    AferoSofthubWifiStateEchoFailed        = 6,
    AferoSofthubWifiStateSSIDNotFound      = 7,
};

/*!
 An array of all available wifi setup attributes.
 */
+ (NSArray<NSNumber *> *_Nonnull)AllWifiSetupAttributes;

/*!
 * The various states when we're either getting the SSID list the hub sees or sending Wifi credentials
 * to the hub
 */

typedef NS_ENUM(NSInteger, AferoSofthubSetupWifiCommandState) {
    
    /** The setup process has started */
    AferoSofthubSetupWifiCommandStateStart     = 0x0,
    
    /** We can see the hub */
    AferoSofthubSetupWifiCommandStateAvailable = 0x1,
    
    /** We've connected to the hub */
    AferoSofthubSetupWifiCommandStateConnected = 0x2,
    
    /** The setup process has finished successfully */
    AferoSofthubSetupWifiCommandStateDone      = 0x3,
    
    /** The setup process has been cancelled */
    AferoSofthubSetupWifiCommandStateCancelled = 0x4,
    
    /** The setup process has timed out because the remote hasn't shown up within BLE range of this hub */
    AferoSofthubSetupWifiCommandStateTimedOutNotAvailable  = 0x5,
    
    /** The setup process has timed out because we couldn't connect to the remote */
    AferoSofthubSetupWifiCommandStateTimedOutConnect  = 0x6,
    
    /** The setup process has timed out because we couldn't finish our communication with the remote */
    AferoSofthubSetupWifiCommandStateTimedOutCommunicating  = 0x7,
    
    /** The setup process has timed out for some other reason */
    AferoSofthubSetupWifiCommandStateTimedOut = 0x8,
    
    /** The setup process has failed for an unknown reason */
    AferoSofthubSetupWifiCommandStateFailed    = 0x9,
};

/**
 * This function will be called to let you know that we've started the Wifi setup process and when it's finished.
 *
 * @param hubId the hub we're sending the Wifi credentials to
 * @param state the SendCredentialState of the setup
 */
typedef void (^AferoSofthubWifiCommandCommandStateChangeCallback)(NSString *_Nonnull hubId, AferoSofthubSetupWifiCommandState state);

/**
 * This function will be called when we need to send some data to another device via the server (like a normal attribute update originating in the UI).
 * The attributeId is the "attrId" value in the JSON, the type is the "type" value in the JSON and if non-empty the hexData is the "data" value in the JSON.
 *
 * @param deviceId      the device to send the update to
 * @param attributeId   the attribute that changed
 * @param type          the type of update
 * @param hexData       the data to send (will be empty if there's no data to send)
 *
 * @return true         the data was sent to the server
 * @return false        the data couldn't be sent to the server
 */
typedef BOOL (^AferoSofthubWriteAttributeCallback)(NSString *_Nonnull deviceId, NSInteger attributeId, NSString *_Nonnull type, NSString *_Nonnull hexData);


/**
 Start the process of sending Wifi credentials to a specific hub.

 @param hubId                       the specific hub you want to send the
                                    Wifi credential to

 @param SSID                        the Wifi SSID (as a UTF8 encoded string)

 @param password                    the Wifi password (as a UTF8 encoded string)

 @param commandStateChangeCallback  a function that will be called to indicate
                                    that we started the process and how it ended

 @param writeAttributeCallback      a function that will send a specific payload
                                    to another device via the server

 @param error                       pointer to an error to be populated if there's
                                    an error.

 @return true                       the command was sent
 @return false                      the command was not sent (see error).
 */

+ (BOOL)sendWifiCredentialToHubWithId:(NSString *_Nonnull)hubId
                                 SSID:(NSString *_Nonnull)SSID
                             password:(NSString *_Nonnull)password
           commandStateChangeCallback:(AferoSofthubWifiCommandCommandStateChangeCallback _Nonnull)commandStateChangeCallback
               writeAttributeCallback:(AferoSofthubWriteAttributeCallback _Nonnull)writeAttributeCallback
                                error:(NSError *_Null_unspecified *_Null_unspecified)error;

/**
 Cancel a previously started sending of Wifi credentials to a specific hub.

 @param hubId       the hub we were trying to setup
 @param error       pointer to an error to be populated if there's an error.
 @return true       the command was canceled
 @return false      the command was not canceled (see error).
 */

+ (BOOL) cancelSendWifiCredentialToHubWithId:(NSString *_Nonnull)hubId
                                       error:(NSError *_Null_unspecified *_Null_unspecified)error;

/**
 Handler for SSID results from the hub.
 */

typedef void (^AferoSofthubWifiListResultHandler)(NSString *_Nonnull deviceId, NSArray<AferoSofthubWifiSSIDEntryWrapper *> *_Nonnull);

/**
 Start the process of getting the Wifi SSID list from a specific hub.
 This will take care of initiating the process but because of the way
 messages are routed in the system (ie. the fact that a hub doesn't get
 attribute updates) to actually get the list will require the app
 to call the below function ParseWifiList() when it gets an update
 for attribute WIFI_SSID_LIST_ATTRIBUTE.

 @param deviceId                    the specific device you want to get
                                    the SSID list from

 @param commandStateChangeCallback  a function that will be called to
                                    indicate that we started the process and how it ended

 @param writeAttributeCallback      a function that will send a specific payload
                                    to another device via the server

 @param wifiListResultHandler       a function that will receive the resulting wifi
                                    list from the server.

 @param error                       pointer to an error to be populated if there's an error.

 @return true                       the command was canceled

 @return false                      the command was not canceled (see error).
 */

+ (BOOL)getWifiSSIDListFromDeviceWithId: (NSString *_Nonnull)deviceId
               commandStateChangeCallback: (AferoSofthubWifiCommandCommandStateChangeCallback _Nonnull)commandStateChangeCallback
                   writeAttributeCallback: (AferoSofthubWriteAttributeCallback _Nonnull)writeAttributeCallback
                    wifiListResultHandler: (AferoSofthubWifiListResultHandler _Nonnull)wifiListResultHandler
                                    error:(NSError *_Null_unspecified *_Null_unspecified)error;

/**
 Cancel a previously started get of a Wifi SSID list from a specific hub.
 @param deviceId  the hub we were trying to get the list from
 @param error     pointer to an error to be populated if there's an error.
 @return true     the command was canceled
 @return false    the command was not canceled (see error).
 */
+ (BOOL)cancelGetWifiSSIDListFromDeviceWithId:(NSString * _Nonnull )deviceId
                                         error:(NSError *_Null_unspecified *_Null_unspecified)error;

/**
 Convert the given RSSI value to bars.
 */

+ (NSNumber *_Nullable)BarsForRSSI:(NSInteger)RSSI
                             error:(NSError *_Null_unspecified *_Null_unspecified)error;

@end
