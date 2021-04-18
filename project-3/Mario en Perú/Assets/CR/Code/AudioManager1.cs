using UnityEngine.Audio;
using System;
using UnityEngine;

public class AudioManager1 : MonoBehaviour
{

	public static AudioManager1 instance;

	public AudioMixerGroup mixerGroup;

	public Sound1[] sounds;

	void Awake()
	{
		if (instance != null)
		{
			Destroy(gameObject);
		}
		else
		{
			instance = this;
			DontDestroyOnLoad(gameObject);
		}

		foreach (Sound1 s in sounds)
		{
			s.source = gameObject.AddComponent<AudioSource>();
			s.source.clip = s.clip;
			s.source.loop = s.loop;

			s.source.outputAudioMixerGroup = mixerGroup;
		}
	}

	public void Play(string sound)
	{
		Sound1 s = Array.Find(sounds, item => item.name == sound);
		if (s == null)
		{
			Debug.LogWarning("Sound: " + name + " not found!");
			return;
		}

		s.source.volume = s.volume * (1f + UnityEngine.Random.Range(-s.volumeVariance / 2f, s.volumeVariance / 2f));
		s.source.pitch = s.pitch * (1f + UnityEngine.Random.Range(-s.pitchVariance / 2f, s.pitchVariance / 2f));

		s.source.Play();
	}

	public void Stop(string name) {
		Sound1 s = Array.Find (sounds, sound => sound.name == name);
		if (s == null) {
			Debug.LogWarning ("Sound: " + name + "not found");
			return;
		}
		s.source.Stop();
	}

	public void Pause(string name) {
		Sound1 s = Array.Find (sounds, sound => sound.name == name);
		if (s == null) {
			Debug.LogWarning ("Sound: " + name + "not found");
			return;
		}
		s.source.Pause();
	}

	void Start(){
		// Play("Victoria Reto");
		// Play("Huir");
		// Play("Alerta");
		// Play("Hit");
		// Play("Death");
		// Play("Begin Combat");
		// Play("Victoria Boss");
	}

}