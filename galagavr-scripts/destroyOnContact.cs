using UnityEngine;
using System.Collections;

public class destroyOnContact : MonoBehaviour {

	// Use this for initialization
	void Start () {
        this.enabled = true;
	}
	
    private void onTriggerEnter(Collider otherEnt)
    {
        print("entity entered trigger");
        Destroy(otherEnt.gameObject);
    }
}
