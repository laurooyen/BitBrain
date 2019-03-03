// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

#pragma once

#include <string>

namespace BB
{
	class Network;

	/// Manager responsible for loading and saving data.

	class FileManager
	{
	public:

		FileManager(const char* networkDir);

		/// Sets a new network name.
		/// This function does not perform any validation in contrast to RequestNetworkName().
		/// @param name The name of the network.
		void SetNetworkName(const char* name);

		/// Gets a new network name from the console.
		/// If this function doesn't get called, networks will be saved to networkDir itself.
		void RequestNetworkName();

		/// Loads a network from a binary file.
		/// Prints the networks settings and asks whether it should be loaded.
		/// @param network The network in which to load the saved data.
		/// @param name The filename (relative to networkDir) of the network which should be loaded.
		void LoadNetwork(Network& network, std::string name) const;

		/// Saves a network to a binary file.
		/// @param network The network to be saved.
		void SaveNetwork(const Network& network) const;

		/// Saves a CSV file of all networks in networkDir.
		/// A separate CSV file will be stored in every subdirectory of networkDir.
		/// Networks that are saved in networkDir itself won't get processed.
		void SaveNetworkCSV() const;

		/// Prints all network settings to the console.
		void DumpNetwork(const Network& network) const;

	private:

		std::string mNetworkDir;
		std::string mNetworkName;

		bool IsAlphaNumeric(char c) const;

		std::string GetTimeStamp() const;
	};
}
