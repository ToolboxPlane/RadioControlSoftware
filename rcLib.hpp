/**
 * @file lib.hpp
 * @author Paul Nykiel
 * @version 0.0
 */

#define RC_LIB_START 0xC9 //201_{10}
#define  RC_LIB_END 0x93 //147_{10}
#define DATA_BUFFER_SIZE 64

#include <stdint.h>

namespace rcLib{
    class Package{
        public:
            /**
             *  Default constructor, should only be used when reading a package
            */
            Package();

            /**
             * Constructor to use when creating a new package
             * @param channelCount  The number of channels used
             * @param resolution The resolution (steps) of each channel.
             */
            Package(uint16_t resolution, uint8_t channelCount);

            /**
             * Convert the package into a serialised byte-array for sending
             * @return a byte array containing the package
             */
            uint8_t encode(void);

            /**
             * Read in the next byte for the package
             * @param  data a byte containing package information
             * @return      a boolean, true when the package is finished
             */
            uint8_t decode(uint8_t data);

            /**
             * Set the value of one channel. The values get ignored if they are
             * not in the valid range.
             * @param  channel the number of the channel starting from 0
             * @param  data    the value of the channel
             */
            void setChannel(uint8_t channel, uint16_t data);

            /**
             * Set the properties of the package if it is a mesh package
             * @param enabled       a boolean whether the message should be mesh message
             * @param routingLength the maximum amount of nodes one package can traverse
             */
            void setMeshProperties(uint8_t enabled = false,
                                    uint8_t routingLength = 8);

            /**
             * Get the id of the original sender of the package
             * @return  a uint8_t containing the id
             */
            uint8_t getDeviceId(void);

            /**
             * Get the resolution (steps) of each channel
             * @return  The resolution as a uint16_t
             */
            uint16_t getResolution(void);

            /**
             * Get the data of one channel
             * @param  channel the number (starting at 0) of the channel
             * @return         the value of the channel
             */
            uint16_t getChannel(uint8_t channel);

            /**
             * Check if the calculated checksum equals the checksum of the package.
             * @return  a boolean whether the checksum is correct
             */
            uint8_t isChecksumCorrect(void);


            /**
             * Read whether the message is a mesh message
             * @return  a boolean wheter the message is a mesh message
             */
            uint8_t isMesh(void);

            /**
             * Checks whether the message has already been forwarded
             * @return true if routingLength is larger 0 and the message is a mesh message
             */
            uint8_t needsForwarding(void);

            /**
             * Counts the current node as traversed node by decrementing
             * the routing Length
             */
            void countNode(void);

            /**
             * Read the data which should get transmitted
             * @return a pointer to the data, the length is returned by the encode function.
             */
            uint8_t* getEncodedData();


        private:
            uint8_t calculateChecksum(uint8_t* data, uint8_t size);
            uint8_t calculateChecksum(void);

            uint8_t resolutionStepsToKey(uint16_t steps);
            uint8_t channelCountToKey(uint16_t channelCount);
            uint16_t keyToResolutionSteps(uint8_t key);
            uint16_t keyToChannelCount(uint8_t key);
            uint8_t resolutionStepsToBitCount(uint16_t steps);

            uint16_t channelData[DATA_BUFFER_SIZE];
            uint8_t buffer[DATA_BUFFER_SIZE];
            uint8_t bufCount;

            uint8_t uid; ///< Unique (package) id
            uint8_t tid; ///< Unique transmitter (device) id
            uint16_t channelCount; ///< Number of saved channels
            uint16_t resolution; ///< Resolution of each channel in pixels

            uint8_t checksum;

            uint8_t mesh;
            uint8_t routingLength;

            static uint8_t globalPackageUid;
            static uint8_t transmitterId;
            static uint8_t errorCount;
    };
}
