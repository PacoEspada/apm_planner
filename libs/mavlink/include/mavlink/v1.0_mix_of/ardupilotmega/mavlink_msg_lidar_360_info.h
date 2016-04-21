// MESSAGE LIDAR_360_INFO PACKING

#define MAVLINK_MSG_ID_LIDAR_360_INFO 199

typedef struct __mavlink_lidar_360_info_t
{
 float left_distance; /*< Left Point Distance (meters)*/
 float right_distance; /*< Right Point Distance (meters)*/
} mavlink_lidar_360_info_t;

#define MAVLINK_MSG_ID_LIDAR_360_INFO_LEN 8
#define MAVLINK_MSG_ID_199_LEN 8

#define MAVLINK_MSG_ID_LIDAR_360_INFO_CRC 171
#define MAVLINK_MSG_ID_199_CRC 171



#define MAVLINK_MESSAGE_INFO_LIDAR_360_INFO { \
	"LIDAR_360_INFO", \
	2, \
	{  { "left_distance", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_lidar_360_info_t, left_distance) }, \
         { "right_distance", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_lidar_360_info_t, right_distance) }, \
         } \
}


/**
 * @brief Pack a lidar_360_info message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param left_distance Left Point Distance (meters)
 * @param right_distance Right Point Distance (meters)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lidar_360_info_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float left_distance, float right_distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LIDAR_360_INFO_LEN];
	_mav_put_float(buf, 0, left_distance);
	_mav_put_float(buf, 4, right_distance);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#else
	mavlink_lidar_360_info_t packet;
	packet.left_distance = left_distance;
	packet.right_distance = right_distance;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LIDAR_360_INFO;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN, MAVLINK_MSG_ID_LIDAR_360_INFO_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#endif
}

/**
 * @brief Pack a lidar_360_info message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param left_distance Left Point Distance (meters)
 * @param right_distance Right Point Distance (meters)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lidar_360_info_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float left_distance,float right_distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LIDAR_360_INFO_LEN];
	_mav_put_float(buf, 0, left_distance);
	_mav_put_float(buf, 4, right_distance);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#else
	mavlink_lidar_360_info_t packet;
	packet.left_distance = left_distance;
	packet.right_distance = right_distance;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LIDAR_360_INFO;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN, MAVLINK_MSG_ID_LIDAR_360_INFO_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#endif
}

/**
 * @brief Encode a lidar_360_info struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param lidar_360_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lidar_360_info_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_lidar_360_info_t* lidar_360_info)
{
	return mavlink_msg_lidar_360_info_pack(system_id, component_id, msg, lidar_360_info->left_distance, lidar_360_info->right_distance);
}

/**
 * @brief Encode a lidar_360_info struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lidar_360_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lidar_360_info_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_lidar_360_info_t* lidar_360_info)
{
	return mavlink_msg_lidar_360_info_pack_chan(system_id, component_id, chan, msg, lidar_360_info->left_distance, lidar_360_info->right_distance);
}

/**
 * @brief Send a lidar_360_info message
 * @param chan MAVLink channel to send the message
 *
 * @param left_distance Left Point Distance (meters)
 * @param right_distance Right Point Distance (meters)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_lidar_360_info_send(mavlink_channel_t chan, float left_distance, float right_distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LIDAR_360_INFO_LEN];
	_mav_put_float(buf, 0, left_distance);
	_mav_put_float(buf, 4, right_distance);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_360_INFO, buf, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN, MAVLINK_MSG_ID_LIDAR_360_INFO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_360_INFO, buf, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#endif
#else
	mavlink_lidar_360_info_t packet;
	packet.left_distance = left_distance;
	packet.right_distance = right_distance;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_360_INFO, (const char *)&packet, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN, MAVLINK_MSG_ID_LIDAR_360_INFO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_360_INFO, (const char *)&packet, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_LIDAR_360_INFO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_lidar_360_info_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float left_distance, float right_distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, left_distance);
	_mav_put_float(buf, 4, right_distance);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_360_INFO, buf, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN, MAVLINK_MSG_ID_LIDAR_360_INFO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_360_INFO, buf, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#endif
#else
	mavlink_lidar_360_info_t *packet = (mavlink_lidar_360_info_t *)msgbuf;
	packet->left_distance = left_distance;
	packet->right_distance = right_distance;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_360_INFO, (const char *)packet, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN, MAVLINK_MSG_ID_LIDAR_360_INFO_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_360_INFO, (const char *)packet, MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE LIDAR_360_INFO UNPACKING


/**
 * @brief Get field left_distance from lidar_360_info message
 *
 * @return Left Point Distance (meters)
 */
static inline float mavlink_msg_lidar_360_info_get_left_distance(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field right_distance from lidar_360_info message
 *
 * @return Right Point Distance (meters)
 */
static inline float mavlink_msg_lidar_360_info_get_right_distance(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a lidar_360_info message into a struct
 *
 * @param msg The message to decode
 * @param lidar_360_info C-struct to decode the message contents into
 */
static inline void mavlink_msg_lidar_360_info_decode(const mavlink_message_t* msg, mavlink_lidar_360_info_t* lidar_360_info)
{
#if MAVLINK_NEED_BYTE_SWAP
	lidar_360_info->left_distance = mavlink_msg_lidar_360_info_get_left_distance(msg);
	lidar_360_info->right_distance = mavlink_msg_lidar_360_info_get_right_distance(msg);
#else
	memcpy(lidar_360_info, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_LIDAR_360_INFO_LEN);
#endif
}
