#pragma once

namespace	ft
{
	/*
		Structure utilisant la propriété du SFINAE (substitution failure is not an error),
		avec comme _value un booléen. Si aucune des substitutions 'spécialisées' ne fonctionnent,
		la _value est mise par défaut a FALSE.		
	*/
	template <typename T>
	struct	is_integral
	{
		static const bool	_value = false;
	};

	template <>
	struct	is_integral<bool>
	{
		static const bool _value = true;
	};

	template <>
	struct	is_integral<char>
	{
		static const bool	_value = true;
	};

	template <>
	struct	is_integral<wchar_t>
	{
		static const bool	_value = true;
	};

	template <>
	struct is_integral<unsigned char>
	{
		static bool const _value = true;
	};

	template <>
	struct is_integral<unsigned short>		
	{
		static bool const _value = true;
	};

	template <>
	struct is_integral<int>
	{
		static bool const _value = true;
	};

	template <>
	struct is_integral<unsigned int>
	{
		static bool const _value = true;
	};

	template <>
	struct	is_integral<short>
	{
		static const bool	_value = true;
	};

	template <>
	struct	is_integral<long>
	{
		static const bool	_value = true;
	};

	template <>
	struct	is_integral<long long>
	{
		static const bool	_value = true;
	};

	template <>
	struct is_integral<unsigned long long>	
	{
		static bool const _value = true;
	};
	/*
		Utilisé pour deux fonctions, assign et insert, et permet d'AUTORISER
		l'utilisation de ces deux fonctions en renvoyant un type void si aucune
		substitution de is_integral n'a réussi a se faire.
	*/

	// structure par défaut si aucune substitution n'a réussi
	template <bool, typename T = void>
	struct enable_if
	{
	};

	/*
		Utilisé avec is_integral, si la substitution de is_integral renvoie
		TRUE, enable_if aura donc un type non VOID!
	*/
	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

}
