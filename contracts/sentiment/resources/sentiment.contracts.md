<h1 class="contract">newproject</h1>

This human-language contract for the `gograssroots` action `newproject` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **project_name** (name of the new project)

* **category** (name of the project's category)

* **creator** (name of the account creating the project)

* **title** (title of the new project)

* **description** (description of the new project)

* **requested** (amount of system tokens requested for the project)

### Intent

The intention of the authors and the invoker of this contract is to...

### Body

I attest that I am the owner or authorized user of this account {{creator}} and...


<h1 class="contract">updateproj</h1>

This human-language contract for the `gograssroots` action `updateproj` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **voter** (name of the account casting its votes)

* **ballot_id** (ID of the ballot measure for which the votes shall be cast)

* **direction** (direction in which votes are cast - 0 = NO, 1 = YES, 2 = ABSTAIN)

### Intent

The intention of the authors and the invoker of this contract is to cast votes in a given ballot measure matching the Member's amount of VOTE tokens in the direction specified by the voter (YES, NO, or ABSTAIN). It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{voter}} and that I intend to cast my VOTE tokens on ballot measure: {{ballot_id}} as: {{direction}}, where the values 0 = NO, 1 = YES, 2 = ABSTAIN. 